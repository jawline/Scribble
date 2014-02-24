%error-verbose
%locations
%name-prefix "scribble_"

%{
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <types.h>
#include <Scribble/Statement/BoolStatement.hpp>
#include <Scribble/Statement/IntStatement.hpp>
#include <Scribble/Statement/OperateStatement.hpp>
#include <Scribble/Statement/StringStatement.hpp>
#include <Scribble/Statement/Float32Statement.hpp>
#include <Scribble/Statement/AssignVariable.hpp>
#include <Scribble/Statement/GetVariableStatement.hpp>
#include <Scribble/Statement/FunctionStatement.hpp>
#include <Scribble/Statement/ForStatement.hpp>
#include <Scribble/Statement/TestStatement.hpp>
#include <Scribble/Statement/IfStatement.hpp>
#include <Scribble/Statement/OperateStatement.hpp>
#include <Scribble/Statement/ReturnStatement.hpp>
#include <Scribble/Statement/TestNilStatement.hpp>
#include <Scribble/Statement/WhileStatement.hpp>
#include <Scribble/Statement/IncrementStatement.hpp>
#include <Scribble/Statement/ArrayStatement.hpp>
#include <Scribble/Statement/AssignArrayStatement.hpp>
#include <Scribble/Statement/GetArrayStatement.hpp>
#include <Scribble/Statement/ArrayLengthStatement.hpp>
#include <Scribble/Statement/AndStatement.hpp>
#include <Scribble/Statement/OrStatement.hpp>
#include <Scribble/Statement/NegativeStatement.hpp>
#include <Scribble/Statement/StructureStatement.hpp>
#include <Scribble/Statement/GetStructureElementStatement.hpp>
#include <Scribble/Statement/StructureAssignElement.hpp>
#include <Scribble/Parser/TypeReference.hpp>
#include <Pointers/SmartPointer.hpp>
#include <Scribble/Function/ScriptedFunction.hpp>
#include <Scribble/Value/TypeManager.hpp>
#include <Scribble/Value/Util.hpp>
#include <Scribble/Parser/Parser.hpp>
#include <Scribble/Value/StructureInfo.hpp>
#include <Scribble/Value/Variable.hpp>

int scribble_lex();
void scribble_error(const char* s);

bool ParsingError;
std::map<std::string, std::string> ImportList;
std::map<std::string, SmartPointer<ScribbleCore::Variable>> Variables;

std::string currentNamespaceName;

std::map<std::string, ScribbleCore::NamespaceType> Namespace;
ScribbleCore::NamespaceType Functions;

std::vector<ScribbleCore::TypeReference> TypeReferences;
std::vector<SmartPointer<ScribbleCore::Variable>> VariableReferences;
std::vector<ScribbleCore::ParserReference> StatementReferences;

int lastuid;

void parser_free_all() {
	ImportList.clear();
	Variables.clear();
	Namespace.clear();
	Functions.clear();
	StatementReferences.clear();
	TypeReferences.clear();
	VariableReferences.clear();
	ParsingError = false;
	lastuid = 0;
}

extern int scribble_lineno;	// defined and maintained in lex.c
extern char *scribble_text;	// defined and maintained in lex.c

%}

%union {
	std::vector<SmartPointer<ScribbleCore::Statement>>* statements;
	std::vector<SmartPointer<ScribbleCore::Variable>>* variables;
	ScribbleCore::StructureInfo* structureinfo;
	ScribbleCore::Statement* statement;
	Function* function;
	SmartPointer<ScribbleCore::Variable>* variable;
	std::string* string;
	
	float32_t float32;
	int integer;
	ScribbleCore::TypeReference* type;
}

%token <string> WORD STRING
%token <float32> FLOAT32
%token <integer> INT
%token <token> PLUS MINUS TIMES DIVIDE EQUALS ASSIGN IF ELSE GREATER LESSER FOR TYPE_ARRAY TYPE_VOID RETURN WHILE NOT IMPORT LINK
%token <token> LPAREN RPAREN LBRACKET RBRACKET COMMA DECREMENT INCREMENT TYPE_BOOL TRUE FALSE AND NIL TYPE
%token <token> FUNCTION VARIABLE STRUCT LENGTH POINT
%token <token> TYPE_INT TYPE_FLOAT32 TYPE_STRING COLON LSQBRACKET RSQBRACKET THEN
%token <token> CONCAT END DO OR PACKAGE

%left PLUS MINUS
%left TIMES DIVIDE
%left TRUE FALSE EQUALS AND OR LINK

%type <statement> Statement;
%type <statements> Program;
%type <variable> Variable;
%type <variable> ArgumentDefinition;
%type <statements> Arguments;
%type <statements> Arguments_2;
%type <statements> Statements;
%type <function> Function;
%type <variables> ArgumentDefinitions;
%type <variables> OptionalArgumentDefinitions;
%type <statement> AutoVariable;
%type <type> Type;
%type <statement> FunctionCall;
%type <structureinfo> BaseStructureInfo;
%type <statements> IfStatements
%type <statement> Expression;

%start Program
%%

Program: {
		lastuid = 0;
		Variables.clear();
		$$ = 0;
	} | Program PACKAGE WORD ASSIGN IMPORT LPAREN STRING RPAREN END {
		ImportList[*$3] = *$7;
		delete $7;
		delete $3;
		$$ = 0;
	} | Program Function {
		$$ = 0;
	} | Program TYPE WORD ASSIGN STRUCT LBRACKET BaseStructureInfo RBRACKET {
		$7->setName(*$3);
		$7->setPackage(currentNamespaceName);
		Functions[*$3] = ScribbleCore::NamespaceEntry(ScribbleCore::TypeReference(new ScribbleCore::TypeReferenceCore(*$3, $7)));
		delete $3;
	}
;

/**
 * BaseStructureInfo is the definition of each field within a structure in the form Name : Type.
 * Accepts 1 or more definition.
 */

BaseStructureInfo: WORD COLON Type {

		$$ = new ScribbleCore::StructureInfo("INVALID");
		
		$$->addInfo(*$1, *$3);
		delete $1;
		delete $3;
		
	} | BaseStructureInfo COMMA WORD COLON Type {
		$$ = $1;
		$$->addInfo(*$3, *$5);
		
		delete $3;
		delete $5;
	}
;

/**
 * Definition of a type. Either a primitive ( int, string, float, bool ) or an array or Structure. NOTE: Structures and arrays are defined 
 * as references which are resolved after parsing to allow for structures which are defined after they are used in the file.
 */

Type: TYPE_INT {
		$$ = new ScribbleCore::TypeReference( new ScribbleCore::TypeReferenceCore ( "", ScribbleCore::getTypeManager().getType(ScribbleCore::Int) ) );
	} | TYPE_STRING {
		$$ = new ScribbleCore::TypeReference ( new ScribbleCore::TypeReferenceCore ( "", ScribbleCore::getTypeManager().getType(ScribbleCore::StringType) ) );
	} | TYPE_FLOAT32 {
		$$ = new ScribbleCore::TypeReference ( new ScribbleCore::TypeReferenceCore ( "", ScribbleCore::getTypeManager().getType(ScribbleCore::Float32)));
	} | TYPE_BOOL {
		$$ = new ScribbleCore::TypeReference ( new ScribbleCore::TypeReferenceCore ( "", ScribbleCore::getTypeManager().getType(ScribbleCore::Boolean) ) );
	} | TYPE_ARRAY LPAREN Type RPAREN {
		$$ = new ScribbleCore::TypeReference ( new ScribbleCore::TypeReferenceCore ( "", ScribbleCore::getTypeManager().getType(ScribbleCore::Array, *$3) ) );
		delete $3;
	} | WORD {
		
		//Set the result to be a new type reference.
		//The type of a type reference will be found after all source files have been parsed and the all types are thus declared.
		
		$$ = new ScribbleCore::TypeReference( new ScribbleCore::TypeReferenceCore ( *$1, nullptr ) );
		TypeReferences.push_back(*$$);
		
		delete $1;

	} | WORD LINK WORD {
	
		//Same as the above except targets a type in a seperate namespace
		$$ = new ScribbleCore::TypeReference ( new ScribbleCore::TypeReferenceCore( *$1, *$3, nullptr) );
		TypeReferences.push_back(*$$);
		
		delete $1;
		delete $3;
		
	}
;

/**
 * The definition of a variable with an explicit type ( var Name : Type )
 */

Variable:  VARIABLE WORD COLON Type {

		//Check if the variable is already defined. If it isn't then create a new one and add a reference to the list of variables so any extra data can be resolved.
		
		auto it = Variables.find(*$2);
			
		if (it != Variables.end()) {
			yyerror("Variable already defined.");
			return -1;
		} else {
			SmartPointer<ScribbleCore::Variable>* nVar = new SmartPointer<ScribbleCore::Variable>(new ScribbleCore::Variable(0, *$4));
			VariableReferences.push_back(*nVar);
			Variables[*$2] = *nVar;
			$$ = nVar;
		}
		
		delete $2;
		delete $4;
	}
;

/**
 * The definition of a variable that has it's type inferred from the type of the expresion it is assigned to.
 */

AutoVariable: VARIABLE WORD ASSIGN Expression {

		auto it = Variables.find(*$2);
				
		if (it != Variables.end()) {
			yyerror("Variable already defined.");
			return -1;
		} else {
		
			ScribbleCore::SafeStatement sp = ScribbleCore::SafeStatement($4);
		
			SmartPointer<ScribbleCore::Variable> nVar = SmartPointer<ScribbleCore::Variable>(new ScribbleCore::Variable(0, nullptr));
			Variables[*$2] = nVar;
			
			ScribbleCore::ParserReference r(ScribbleCore::AutoVariablePair(nVar, sp));
			StatementReferences.push_back(r);

			$$ = new ScribbleCore::AssignVariableStatement(scribble_lineno, scribble_text, nVar, sp);
		}
		
		delete $2;
	}
;

/**
 * Defines the syntax of an argument, written like Name : Type
 */

ArgumentDefinition: WORD COLON Type {

		auto it = Variables.find(*$1);

		if (it != Variables.end()) {
			yyerror("Variable already defined.");
			return -1;
		} else {
			SmartPointer<ScribbleCore::Variable>* nVar = new SmartPointer<ScribbleCore::Variable>(new ScribbleCore::Variable(0, *$3));
			VariableReferences.push_back(*nVar);
			Variables[*$1] = *nVar;
			$$ = nVar;
		}
		
		delete $1;
		delete $3;
	}
;

/**
 * Accept zero or more argument definitions
 */

OptionalArgumentDefinitions: {
		$$ = new std::vector<SmartPointer<ScribbleCore::Variable>>();
	} | ArgumentDefinitions {
		$$ = $1;
	}
;

/**	
 * Accept one or more argument definitions in the form Name : Type, Name : Type..
 */

ArgumentDefinitions: ArgumentDefinition {
		$$ = new std::vector<SmartPointer<ScribbleCore::Variable>>();
		$$->push_back(*$1);
		delete $1;
	} | ArgumentDefinitions COMMA ArgumentDefinition {
		$$ = $1;
		$$->push_back(*$3);
		delete $3;
	}
;

/**
 * The definition of a function. func Name ( Arguments ) { Code } defines a function of void type
 * and func Name ( Arguments ) : Type { Code } defines a function of a specific type.
 */

Function: FUNCTION WORD LPAREN OptionalArgumentDefinitions RPAREN COLON Type LBRACKET Statements RBRACKET {
		std::vector<SmartPointer<ScribbleCore::Variable>> values;

		int pos = 0;
		for (auto it = Variables.begin(); it != Variables.end(); it++) {
			it->second->setPosition(pos);
			values.push_back(it->second);
			pos++;
		}


		SmartPointer<ScribbleCore::Variable> returnTemplate = SmartPointer<ScribbleCore::Variable>(new ScribbleCore::Variable(0, *$7));
		VariableReferences.push_back(returnTemplate);
		
		SmartPointer<API::Function> fn = SmartPointer<API::Function>( new ScribbleCore::ScriptedFunction(*$2, lastuid++, currentNamespaceName, *$7, returnTemplate, *$9, values, *$4));
		
		if (Functions[*$2].type() == ScribbleCore::EmptyEntry) {
		
			std::vector<SafeFunction> newSet;
			newSet.push_back(fn);

			Functions[*$2] = ScribbleCore::NamespaceEntry(newSet);
		
		} else {
		
			if ( Functions[*$2].type() != ScribbleCore::FunctionSetEntry) {
				yyerror("Not a function type");
				return -1;
			}
			
			std::vector<SafeFunction> functions = Functions[*$2].getFunctionSet();
			
			Functions[*$2].addFunctionToSet(fn);
		
		}
		
		Variables.clear();
		
		//Delete name
		delete $2;
		
		//Delete statements vector
		delete $9;
		
		//Delete variables vector
		delete $4;
		
		delete $7;

	} | FUNCTION WORD LPAREN OptionalArgumentDefinitions RPAREN LBRACKET Statements RBRACKET {
		std::vector<SmartPointer<ScribbleCore::Variable>> values;

		int pos = 0;
		for (auto it = Variables.begin(); it != Variables.end(); it++) {
			it->second->setPosition(pos);
			values.push_back(it->second);
			pos++;
		}

		ScribbleCore::TypeReference voidReference = ScribbleCore::TypeReference( new ScribbleCore::TypeReferenceCore ( "", ScribbleCore::getVoidType() ) );

		SmartPointer<ScribbleCore::Variable> returnTemplate = SmartPointer<ScribbleCore::Variable>(new ScribbleCore::Variable(0, voidReference));
		
		SmartPointer<API::Function> fn = SmartPointer<API::Function>(new ScribbleCore::ScriptedFunction(*$2, lastuid++, currentNamespaceName, voidReference, returnTemplate, *$7, values, *$4));
		
		if (Functions[*$2].type() == ScribbleCore::EmptyEntry) {
		
			std::vector<API::SafeFunction> newSet;
			newSet.push_back(fn);

			Functions[*$2] = ScribbleCore::NamespaceEntry(newSet);
		
		} else {
		
			if ( Functions[*$2].type() != ScribbleCore::FunctionSetEntry) {
				yyerror("Not a function type");
				return -1;
			}
			
			std::vector<API::SafeFunction> functions = Functions[*$2].getFunctionSet();
			
			Functions[*$2].addFunctionToSet(fn);
		
		}
		
		Variables.clear();
		
		//Delete name
		delete $2;
		
		//Delete statements vector
		delete $7;
		
		//Delete variables vector
		delete $4;

	}
;

/**
 * Defines the arguments for a functional call or structure constructor.
 */
 
Arguments: {
		$$ = new std::vector<SmartPointer<ScribbleCore::Statement>>();
	} | Arguments_2 {
		$$ = $1;
	}
;

Arguments_2: Expression {
		$$ = new std::vector<SmartPointer<ScribbleCore::Statement>>();
		$$->push_back(ScribbleCore::SafeStatement($1));
	} | Arguments COMMA Expression {
		$$ = $1;
		$$->push_back(ScribbleCore::SafeStatement($3));
	}
;

/**
 * Define statements as zero or more Statement rules.
 */

Statements: {
		$$ = new std::vector<SmartPointer<ScribbleCore::Statement>>();
	} | Statements Statement {
		$$ = $1;
		$$->push_back(ScribbleCore::SafeStatement($2));
	} | Statements RETURN {
		$$ = $1;
		$$->push_back( ScribbleCore::SafeStatement( new ScribbleCore::ReturnStatement(scribble_lineno, scribble_text, nullptr)));
	}
;

/**
 * Defines a functional call as either Name ( Args ) or Package.Name ( Args ).
 */

FunctionCall: WORD LPAREN Arguments RPAREN {
	
		std::vector<SmartPointer<ScribbleCore::Statement>> args;
	
		for (unsigned int i = 0; i < $3->size(); ++i) {
			args.push_back($3->at(i));
		}
	
		delete $3;
		
		SmartPointer<ScribbleCore::FunctionReference> reference = SmartPointer<ScribbleCore::FunctionReference>(new ScribbleCore::FunctionReference("", *$1, args, 0));
		ScribbleCore::ParserReference r(reference);
		StatementReferences.push_back(r);
		
		
		$$ = new ScribbleCore::FunctionStatement(scribble_lineno, scribble_text, reference, Variables.size());
		
		//Free the name pointer
		delete $1;
		
	} | WORD LINK WORD LPAREN Arguments RPAREN {
	
		std::vector<SmartPointer<ScribbleCore::Statement>> args;
	
		for (unsigned int i = 0; i < $5->size(); ++i) {
			args.push_back($5->at(i));
		}
	
		delete $5;
	
		SmartPointer<ScribbleCore::FunctionReference> reference = SmartPointer<ScribbleCore::FunctionReference>(new ScribbleCore::FunctionReference(*$1, *$3, args, 0));
	
		ScribbleCore::ParserReference r(reference);
		StatementReferences.push_back(r);
		
		$$ = new ScribbleCore::FunctionStatement(scribble_lineno, scribble_text, reference, Variables.size());
	
		//Free the name pointers
		delete $1;
		delete $3;
	}
;

/**
 * either a single Statement or many statements inside some curly brackets { }.
 */

IfStatements: Statement {
		std::vector<ScribbleCore::SafeStatement>* stmts = new std::vector<ScribbleCore::SafeStatement>();
		stmts->push_back(ScribbleCore::SafeStatement($1));
		$$ = stmts;
	} | LBRACKET Statements RBRACKET {
		$$ = $2;
	}
;

/**
 * Defines a statement as either one of the three control 
 * structures, a return statement or an expression.
 */

Statement: Expression END {
		$$ = $1;
	} | IF Expression THEN IfStatements  {
		$$ = new ScribbleCore::IfStatement(scribble_lineno, scribble_text, ScribbleCore::SafeStatement($2), *$4, std::vector<SmartPointer<ScribbleCore::Statement>>());
		delete $4;
	} | IF Expression THEN IfStatements ELSE IfStatements {
		$$ = new ScribbleCore::IfStatement(scribble_lineno, scribble_text, ScribbleCore::SafeStatement($2), *$4, *$6);
		delete $4;
		delete $6;
	} | FOR Expression END Expression END Expression DO IfStatements {
		$$ = new ScribbleCore::ForStatement(scribble_lineno, scribble_text, ScribbleCore::SafeStatement($2), ScribbleCore::SafeStatement($4), ScribbleCore::SafeStatement($6), *$8);
		delete $8;
	} | WHILE Expression DO LBRACKET Statements RBRACKET {
		$$ = new ScribbleCore::WhileStatement(scribble_lineno, scribble_text, ScribbleCore::SafeStatement($2), *$5);
		delete $5;
	} | RETURN Expression END {	
		$$ = new ScribbleCore::ReturnStatement(scribble_lineno, scribble_text, ScribbleCore::SafeStatement($2));	
	}
;

Expression: MINUS Expression {
		$$ = new ScribbleCore::NegativeStatement(scribble_lineno, scribble_text, ScribbleCore::SafeStatement($2));
	} | TRUE {
		$$ = new ScribbleCore::BoolStatement(scribble_lineno, scribble_text, true);
	} | FALSE {
		$$ = new ScribbleCore::BoolStatement(scribble_lineno, scribble_text, false);
	} | INT {
		$$ = new ScribbleCore::IntStatement(scribble_lineno, scribble_text, $1);
	} | FLOAT32 {
		$$ = new ScribbleCore::Float32Statement(scribble_lineno, scribble_text, $1);
	} | STRING {
		$$ = new ScribbleCore::StringStatement(scribble_lineno, scribble_text, *$1);

		//Free string pointer
		delete $1;
	} | Type LBRACKET Arguments RBRACKET {
		$$ = new ScribbleCore::StructureStatement(scribble_lineno, scribble_text, *$1, *$3);
		delete $3;
		delete $1;
	} | Variable {
		$$ = new ScribbleCore::GetVariableStatement(scribble_lineno, scribble_text, *$1);
		delete $1;
	} | Variable ASSIGN Expression {
		$$ = new ScribbleCore::AssignVariableStatement(scribble_lineno, scribble_text, *$1, ScribbleCore::SafeStatement($3));
		delete $1;
	} | AutoVariable {
		$$ = $1;
	} | LENGTH LPAREN Expression RPAREN {
		$$ = new ScribbleCore::ArrayLengthStatement(scribble_lineno, scribble_text, ScribbleCore::SafeStatement($3));
	} | LSQBRACKET Expression RSQBRACKET Type {
		$$ = new ScribbleCore::ArrayStatement(scribble_lineno, scribble_text, ScribbleCore::getTypeManager().getType(ScribbleCore::Array, *$4), ScribbleCore::SafeStatement($2));
		delete $4;
	} | Expression LSQBRACKET Expression RSQBRACKET ASSIGN Expression {
		$$ = new ScribbleCore::AssignArrayStatement(scribble_lineno, scribble_text, ScribbleCore::SafeStatement($1), ScribbleCore::SafeStatement($6), ScribbleCore::SafeStatement($3));
	} | Expression LSQBRACKET Expression RSQBRACKET {
		$$ = new ScribbleCore::GetArrayStatement(scribble_lineno, scribble_text, ScribbleCore::SafeStatement($1), ScribbleCore::SafeStatement($3)); 
	} | FunctionCall {
		$$ = $1;
	} | Expression PLUS Expression {
		$$ = new ScribbleCore::OperateStatement(scribble_lineno, scribble_text, ScribbleCore::Add, ScribbleCore::SafeStatement($1), ScribbleCore::SafeStatement($3));
	} | Expression MINUS Expression {
		$$ = new ScribbleCore::OperateStatement(scribble_lineno, scribble_text, ScribbleCore::Subtract, ScribbleCore::SafeStatement($1), ScribbleCore::SafeStatement($3));
	} | Expression TIMES Expression {
		$$ = new ScribbleCore::OperateStatement(scribble_lineno, scribble_text, ScribbleCore::Multiply, ScribbleCore::SafeStatement($1), ScribbleCore::SafeStatement($3));
	} | Expression DIVIDE Expression {
		$$ = new ScribbleCore::OperateStatement(scribble_lineno, scribble_text, ScribbleCore::Divide, ScribbleCore::SafeStatement($1), ScribbleCore::SafeStatement($3));
	} | NIL EQUALS Expression {
		$$ = new ScribbleCore::TestNilStatement(scribble_lineno, scribble_text, ScribbleCore::SafeStatement($3));
	} | Expression EQUALS NIL {
		$$ = new ScribbleCore::TestNilStatement(scribble_lineno, scribble_text, ScribbleCore::SafeStatement($1));
	} | Expression EQUALS Expression {
		$$ = new ScribbleCore::TestStatement(scribble_lineno, scribble_text, ScribbleCore::TestEquals, ScribbleCore::SafeStatement($1), ScribbleCore::SafeStatement($3));
	} | Expression NOT EQUALS Expression {
		$$ = new ScribbleCore::TestStatement(scribble_lineno, scribble_text, ScribbleCore::TestNotEquals, ScribbleCore::SafeStatement($1), ScribbleCore::SafeStatement($4));
	} | Expression GREATER Expression {
		$$ = new ScribbleCore::TestStatement(scribble_lineno, scribble_text, ScribbleCore::TestGreater, ScribbleCore::SafeStatement($1), ScribbleCore::SafeStatement($3));
	} | Expression LESSER Expression {
		$$ = new ScribbleCore::TestStatement(scribble_lineno, scribble_text, ScribbleCore::TestLess, ScribbleCore::SafeStatement($1), ScribbleCore::SafeStatement($3));
	} | Expression LESSER EQUALS Expression {
		$$ = new ScribbleCore::TestStatement(scribble_lineno, scribble_text, ScribbleCore::TestLessOrEqual, ScribbleCore::SafeStatement($1), ScribbleCore::SafeStatement($4));
	} | Expression GREATER EQUALS Expression {
		$$ = new ScribbleCore::TestStatement(scribble_lineno, scribble_text, ScribbleCore::TestGreaterOrEqual, ScribbleCore::SafeStatement($1), ScribbleCore::SafeStatement($4));
	} | LPAREN Expression RPAREN {
		$$ = $2;
	} | WORD ASSIGN Expression {
		
		auto it = Variables.find(*$1);

		if (it == Variables.end()) {
			scribble_error((std::string(*$1) + " is not defined").c_str());
		} else {
			$$ = new ScribbleCore::AssignVariableStatement(scribble_lineno, scribble_text, it->second, ScribbleCore::SafeStatement($3));
		}
		
		//Free up string pointer.
		delete $1;
		
	} | Expression CONCAT Expression {

		std::vector<ScribbleCore::SafeStatement> args;
		args.push_back(ScribbleCore::SafeStatement($1));
		args.push_back(ScribbleCore::SafeStatement($3));
	
		SmartPointer<ScribbleCore::FunctionReference> reference = SmartPointer<ScribbleCore::FunctionReference>(new ScribbleCore::FunctionReference("__system", "Concat", args, 0));
	
		ScribbleCore::ParserReference r(reference);
		StatementReferences.push_back(r);
		
		$$ = new ScribbleCore::FunctionStatement(scribble_lineno, scribble_text, reference, Variables.size());
	
	} | WORD INCREMENT {
	
		auto it = Variables.find(*$1);
		
		if (it == Variables.end()) {
			scribble_error((std::string(*$1) + " is not defined").c_str());
		} else {
			$$ = new ScribbleCore::IncrementStatement(scribble_lineno, scribble_text, it->second, ScribbleCore::Increment, false);
		}
		
		//Free name pointer
		delete $1;
		
	} | INCREMENT WORD {
		
		auto it = Variables.find(*$2);
		
		if (it == Variables.end()) {
			scribble_error((std::string(*$2) + " is not defined").c_str());
		} else {
			$$ = new ScribbleCore::IncrementStatement(scribble_lineno, scribble_text, it->second, ScribbleCore::Increment, true);
		}
		
		//Free name pointer
		delete $2;
		
	} | WORD DECREMENT {
		
		auto it = Variables.find(*$1);
		
		if (it == Variables.end()) {
			scribble_error((std::string(*$1) + " is not defined").c_str());
		} else {
			$$ = new ScribbleCore::IncrementStatement(scribble_lineno, scribble_text, it->second, ScribbleCore::Decrement, false);
		}
		
		//Free name pointer
		delete $1;
		
	} | DECREMENT WORD {
		
		auto it = Variables.find(*$2);
		
		if (it == Variables.end()) {
			scribble_error((std::string(*$2) + " is not defined").c_str());
		} else {
			$$ = new ScribbleCore::IncrementStatement(scribble_lineno, scribble_text, it->second, ScribbleCore::Decrement, true);
		}
		
		//Free name pointer
		delete $2;
	} | Expression AND Expression {
		$$ = new ScribbleCore::AndStatement(scribble_lineno, scribble_text, ScribbleCore::SafeStatement($1), ScribbleCore::SafeStatement($3));
	} | Expression OR Expression {
		$$ = new ScribbleCore::OrStatement(scribble_lineno, scribble_text, ScribbleCore::SafeStatement($1), ScribbleCore::SafeStatement($3));
	} | Expression POINT WORD {
		
		$$ = new ScribbleCore::GetStructureElementStatement(scribble_lineno, scribble_text, ScribbleCore::SafeStatement($1), *$3);
		
		ScribbleCore::ParserReference r((ScribbleCore::GetStructureElementStatement*) $$);
		StatementReferences.push_back(r);
		
		delete $3;
	} | Expression POINT WORD ASSIGN Expression {
	
		$$ = new ScribbleCore::StructureAssignElement(scribble_lineno, scribble_text, ScribbleCore::SafeStatement($1), ScribbleCore::SafeStatement($5), *$3);
		
		ScribbleCore::ParserReference r((ScribbleCore::StructureAssignElement*) $$);
		StatementReferences.push_back(r);
	
		delete $3;
	} | WORD {

		auto it = Variables.find(*$1);

		if (it == Variables.end()) {
			scribble_error((std::string("Variable '") + std::string(*$1) + "' is not defined").c_str());
			return -1;
		} else {
			$$ = new ScribbleCore::GetVariableStatement(scribble_lineno, scribble_text, it->second);
		}

		//Free name pointer
		delete $1;
		
	}
;

%%

void scribble_error(std::string s)
{

  printf("ERROR: %s at symbol %s on line %i\n", s.c_str(), scribble_text, scribble_lineno);
  ParsingError = true;
}

void scribble_error(const char* s)
{
  scribble_error(std::string(s));
}

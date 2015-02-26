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
#include <Scribble/Statement/TernaryStatement.hpp>
#include <Scribble/Statement/FunctionStatement.hpp>
#include <Scribble/Statement/ForStatement.hpp>
#include <Scribble/Statement/TestStatement.hpp>
#include <Scribble/Statement/IfStatement.hpp>
#include <Scribble/Statement/OperateStatement.hpp>
#include <Scribble/Statement/ReturnStatement.hpp>
#include <Scribble/Statement/NilStatement.hpp>
#include <Scribble/Statement/WhileStatement.hpp>
#include <Scribble/Statement/IncrementStatement.hpp>
#include <Scribble/Statement/ArrayStatement.hpp>
#include <Scribble/Statement/AssignArrayStatement.hpp>
#include <Scribble/Statement/GetArrayStatement.hpp>
#include <Scribble/Statement/ArrayLengthStatement.hpp>
#include <Scribble/Statement/FunctionReferenceStatement.hpp>
#include <Scribble/Statement/AndStatement.hpp>
#include <Scribble/Statement/OrStatement.hpp>
#include <Scribble/Statement/NegativeStatement.hpp>
#include <Scribble/Statement/StructureStatement.hpp>
#include <Scribble/Statement/GetStructureElementStatement.hpp>
#include <Scribble/Statement/StructureAssignElement.hpp>
#include <Scribble/Statement/CallFunctionReference.hpp>
#include <Scribble/Statement/NotStatement.hpp>
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
std::vector<SmartPointer<ScribbleCore::Variable>> Variables;

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

SmartPointer<ScribbleCore::Variable> findVariable(std::string name) {

	for (unsigned int i = 0; i < Variables.size(); i++) {
		if (name.compare(Variables[i]->getName()) == 0) {
			return Variables[i];
		}
	}

	return SmartPointer<ScribbleCore::Variable>(nullptr);
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
	std::vector<ScribbleCore::TypeReference>* types;
	std::string* string;
	float32_t float32;
	int integer;
	ScribbleCore::TypeReference* type;
	void* void_t;
}

%token <string> WORD STRING
%token <float32> FLOAT32
%token <integer> INT AMP
%token <token> PLUS MINUS TIMES DIVIDE EQUALS ASSIGN IF ELSE GREATER LESSER GREATER_EQUAL LESSER_EQUAL FOR TYPE_ARRAY RETURN WHILE NOT NOT_EQUAL IMPORT LINK
%token <token> LPAREN RPAREN LBRACKET RBRACKET COMMA DECREMENT INCREMENT PLUS_ASSIGN MINUS_ASSIGN TYPE_BOOL TRUE FALSE AND NIL TYPE
%token <token> FUNCTION VARIABLE STRUCT LENGTH POINT
%token <token> TYPE_INT TYPE_FLOAT32 TYPE_STRING COLON LSQBRACKET RSQBRACKET THEN
%token <token> TERNARY CONCAT END DO OR PACKAGE IS GUARD OTHERWISE BETWEEN


%left END BETWEEN
%right VAR IF FOR WHILE RETURN
%left LPAREN RPAREN LBRACKET RBRACKET
%left COMMA
%left AND OR LINK LEN
%right ASSIGN MINUS_ASSIGN PLUS_ASSIGN
%left EQUALS
%left GREATER LESSER GREATER_EQUAL LESSER_EQUAL NOT_EQUAL
%left TIMES DIVIDE
%left PLUS MINUS
%right NOT

%type <statement> Statement;
%type <statements> Program;
%type <variable> Variable;
%type <variable> ArgumentDefinition;
%type <variable> IntVariable;
%type <statements> Arguments;
%type <statements> Arguments_2;
%type <statements> Statements;
%type <function> Function;
%type <variables> ArgumentDefinitions;
%type <variables> OptionalArgumentDefinitions;
%type <statement> AutoVariable;
%type <statement> GuardOrExpression;
%type <statement> Guard;
%type <type> Type;
%type <statement> FunctionCall;
%type <structureinfo> BaseStructureInfo;
%type <statements> IfStatements
%type <statement> Expression;
%type <statement> FunctionReference;
%type <types> MultipleTypes;
%type <types> MultipleTypes_2;
%type <void_t> PackageList
	
%start Program
%%

Program: {
		lastuid = 0;
		Variables.clear();
		$$ = 0;
	} | Program PACKAGE PackageList END {
	} | Program Function {
		$$ = 0;
	} | Program TYPE WORD ASSIGN STRUCT LBRACKET BaseStructureInfo RBRACKET {
		$7->setName(*$3);
		$7->setPackage(currentNamespaceName);
		Functions[*$3] = ScribbleCore::NamespaceEntry(ScribbleCore::TypeReference(new ScribbleCore::TypeReferenceCore(*$3, $7)));
		delete $3;
	};

PackageList: WORD ASSIGN IMPORT LPAREN STRING RPAREN {
		ImportList[*$1] = *$5;
		delete $5;
		delete $1;
		$$ = 0;
} | PackageList COMMA WORD ASSIGN IMPORT LPAREN STRING RPAREN {
		ImportList[*$3] = *$7;
		delete $7;
		delete $3;
		$$ = 0;
};

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
	};

/**
 * Definition of a type. Either a primitive ( int, string, float, bool ) or an array or Structure. NOTE: Structures and arrays are defined 
 * as references which are resolved after parsing to allow for structures which are defined after they are used in the file.
 */
Type: TYPE_INT {
		$$ = new ScribbleCore::TypeReference( new ScribbleCore::TypeReferenceCore ( "int", ScribbleCore::getTypeManager().getType(ScribbleCore::Int) ) );
	} | TYPE_STRING {
		$$ = new ScribbleCore::TypeReference ( new ScribbleCore::TypeReferenceCore ( "string", ScribbleCore::getTypeManager().getType(ScribbleCore::StringType) ) );
	} | TYPE_FLOAT32 {
		$$ = new ScribbleCore::TypeReference ( new ScribbleCore::TypeReferenceCore ( "float32", ScribbleCore::getTypeManager().getType(ScribbleCore::Float32)));
	} | TYPE_BOOL {
		$$ = new ScribbleCore::TypeReference ( new ScribbleCore::TypeReferenceCore ( "bool", ScribbleCore::getTypeManager().getType(ScribbleCore::Boolean) ) );
	} | TYPE_ARRAY LPAREN Type RPAREN {
		$$ = new ScribbleCore::TypeReference ( new ScribbleCore::TypeReferenceCore ( "array", ScribbleCore::getTypeManager().getType(ScribbleCore::Array, *$3) ) );
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
		
	} | FUNCTION LPAREN MultipleTypes RPAREN {
		$$ = new ScribbleCore::TypeReference ( new ScribbleCore::TypeReferenceCore ( "function", ScribbleCore::getTypeManager().getType(*$3, ScribbleCore::makeTypeReference(ScribbleCore::getVoidType())) ) );
		delete $3;
	} | FUNCTION LPAREN MultipleTypes RPAREN POINT Type {
		$$ = new ScribbleCore::TypeReference ( new ScribbleCore::TypeReferenceCore ( "function", ScribbleCore::getTypeManager().getType(*$3, *$6) ) );
		delete $3;
		delete $6;
	};

MultipleTypes: {
 $$ = new std::vector<ScribbleCore::TypeReference>();
} | MultipleTypes_2 {
 $$ = $1;
}

MultipleTypes_2: Type {
	$$ = new std::vector<ScribbleCore::TypeReference>;
	$$->push_back(*$1);
	delete $1;
} | MultipleTypes_2 COMMA Type {
	$$ = $1;
	$$->push_back(*$3);
	delete $3;
};

/**
 * The definition of a variable with an explicit type ( var Name : Type )
 */
Variable:  VARIABLE WORD COLON Type {

		//Check if the variable is already defined.
		//If it isn't then create a new one and add a
		//reference to the list of variables so any extra data can be resolved.
		
		auto it = findVariable(*$2);
			
		if (it.get() != nullptr) {
			yyerror("Variable already defined.");
			return -1;
		} else {
			SmartPointer<ScribbleCore::Variable>* nVar = new SmartPointer<ScribbleCore::Variable>(new ScribbleCore::Variable(*$2, 0, *$4));
			VariableReferences.push_back(*nVar);
			Variables.push_back(*nVar);
			$$ = nVar;
		}
		
		delete $2;
		delete $4;
	};

/**
 * The definition of a variable that has it's type inferred from the type of the expresion it is assigned to.
 */
AutoVariable: VARIABLE WORD ASSIGN Expression {

		auto it = findVariable(*$2);
				
		if (it.get() != nullptr) {
			yyerror("Variable already defined.");
			return -1;
		} else {
		
			ScribbleCore::SafeStatement sp = ScribbleCore::SafeStatement($4);
		
			SmartPointer<ScribbleCore::Variable> nVar = SmartPointer<ScribbleCore::Variable>(new ScribbleCore::Variable(*$2, 0, sp->type()));
			VariableReferences.push_back(nVar);
			Variables.push_back(nVar);
			
			$$ = new ScribbleCore::AssignVariableStatement(scribble_lineno, scribble_text, nVar, sp);
		}
		
		delete $2;
	};
	
/**
 * Gives syntax for variable declaration when the new variable is guarenteed to be an integer (for var i between 0 and x)
 */
IntVariable: VARIABLE WORD {

		//Check if the variable is already defined.
		//If it isn't then create a new one and add a
		//reference to the list of variables so any extra data can be resolved.
		
		auto it = findVariable(*$2);
			
		if (it.get() != nullptr) {
			yyerror("Variable already defined.");
			return -1;
		} else {
			auto intTypeReference = ScribbleCore::TypeReference(new ScribbleCore::TypeReferenceCore("int", ScribbleCore::getTypeManager().getType(ScribbleCore::Int)));
			SmartPointer<ScribbleCore::Variable>* nVar = new SmartPointer<ScribbleCore::Variable>(new ScribbleCore::Variable(*$2, 0, intTypeReference));
			VariableReferences.push_back(*nVar);
			Variables.push_back(*nVar);
			$$ = nVar;
		}
		
		delete $2;
	};

/**
 * Defines the syntax of an argument, written like Name : Type
 */
ArgumentDefinition: WORD COLON Type {

		auto it = findVariable(*$1);

		if (it.get() != nullptr) {
			yyerror("Argument with the same name already defined.");
			return -1;
		} else {
			SmartPointer<ScribbleCore::Variable>* nVar = new SmartPointer<ScribbleCore::Variable>(new ScribbleCore::Variable(*$1, 0, *$3));
			VariableReferences.push_back(*nVar);
			Variables.push_back(*nVar);
			$$ = nVar;
		}
		
		delete $1;
		delete $3;
	};

/**
 * Accept zero or more argument definitions
 */
OptionalArgumentDefinitions: {
		$$ = new std::vector<SmartPointer<ScribbleCore::Variable>>();
	} | ArgumentDefinitions {
		$$ = $1;
	};

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
	};

/**
 * The definition of a function. func Name ( Arguments ) { Code } defines a function of void type
 * and func Name ( Arguments ) : Type { Code } defines a function of a specific type.
 */
Function: FUNCTION WORD LPAREN OptionalArgumentDefinitions RPAREN POINT Type LBRACKET Statements RBRACKET {
		std::vector<SmartPointer<ScribbleCore::Variable>> values;

		for (unsigned int i = 0; i < Variables.size(); i++) {
			Variables[i]->setPosition(i);
			values.push_back(Variables[i]);
		}

		//Generate the function signature with all the type info about the fn
		std::vector<ScribbleCore::TypeReference> arguments;
		
		for (unsigned int i = 0; i < $4->size(); i++) {
		 arguments.push_back($4->at(i)->getTypeReference());
		}
		
		ScribbleCore::FunctionSignature signature(arguments, *$7);
		
		SmartPointer<API::Function> fn = SmartPointer<API::Function>( new ScribbleCore::ScriptedFunction(*$2, lastuid++, currentNamespaceName, *$9, values, signature));
		
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

		for (unsigned int i = 0; i < Variables.size(); i++) {
			Variables[i]->setPosition(i);
			values.push_back(Variables[i]);
		}

		//Generate the function signature
		ScribbleCore::TypeReference voidReference = ScribbleCore::TypeReference( new ScribbleCore::TypeReferenceCore ( "", ScribbleCore::getVoidType() ) );

		std::vector<ScribbleCore::TypeReference> arguments;
		
		for (unsigned int i = 0; i < $4->size(); i++) {
		 arguments.push_back($4->at(i)->getTypeReference());
		}
		
		ScribbleCore::FunctionSignature signature(arguments, voidReference);
		
		SmartPointer<API::Function> fn = SmartPointer<API::Function>(new ScribbleCore::ScriptedFunction(*$2, lastuid++, currentNamespaceName, *$7, values, signature));
		
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

	} | FUNCTION WORD LPAREN OptionalArgumentDefinitions RPAREN POINT Type ASSIGN GuardOrExpression {
		std::vector<SmartPointer<ScribbleCore::Variable>> values;

		for (unsigned int i = 0; i < Variables.size(); i++) {
			Variables[i]->setPosition(i);
			values.push_back(Variables[i]);
		}

		//Generate the function signature with all the type info about the fn
		std::vector<ScribbleCore::TypeReference> arguments;
		
		for (unsigned int i = 0; i < $4->size(); i++) {
		 arguments.push_back($4->at(i)->getTypeReference());
		}
		
		SmartPointer<ScribbleCore::Statement> returnedStatement = SmartPointer<ScribbleCore::Statement>($9); 
		
		ScribbleCore::FunctionSignature signature(arguments, *$7);
		std::vector<SmartPointer<ScribbleCore::Statement>> statements;
		statements.push_back(returnedStatement);
		
		SmartPointer<API::Function> fn = SmartPointer<API::Function>( new ScribbleCore::ScriptedFunction(*$2, lastuid++, currentNamespaceName, statements, values, signature));
		
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
		//Delete variables vector
		delete $4;
		delete $7;
	};

/**
 * Defines the arguments for a functional call or structure constructor.
 */
Arguments: {
		$$ = new std::vector<SmartPointer<ScribbleCore::Statement>>();
	} | Arguments_2 {
		$$ = $1;
	};

Arguments_2: Expression {
		$$ = new std::vector<SmartPointer<ScribbleCore::Statement>>();
		$$->push_back(ScribbleCore::SafeStatement($1));
	} | Arguments COMMA Expression {
		$$ = $1;
		$$->push_back(ScribbleCore::SafeStatement($3));
	};

/**
 * Define statements as zero or more Statement rules.
 */
Statements: {
		$$ = new std::vector<SmartPointer<ScribbleCore::Statement>>();
	} | Statements Statement {
		$$ = $1;
		$$->push_back(ScribbleCore::SafeStatement($2));
	};

/**
 * Defines a function reference as Name(Type,Type,Type)
 */
FunctionReference: AMP WORD LPAREN MultipleTypes RPAREN {
	std::vector<ScribbleCore::TypeReference> argTypes = *$4;
	
	SmartPointer<ScribbleCore::FunctionReference> reference = SmartPointer<ScribbleCore::FunctionReference>(new ScribbleCore::FunctionReference("", *$2, argTypes, 0));
	ScribbleCore::ParserReference r(reference);
	StatementReferences.push_back(r);
	
	$$ = new ScribbleCore::FunctionReferenceStatement(scribble_lineno, scribble_text, reference);
	
	ScribbleCore::ParserReference q($$);
	StatementReferences.push_back(q);
	
	delete $2;
	delete $4;
} | AMP WORD LINK WORD LPAREN MultipleTypes RPAREN {
	std::vector<ScribbleCore::TypeReference> argTypes = *$6;
	
	SmartPointer<ScribbleCore::FunctionReference> reference = SmartPointer<ScribbleCore::FunctionReference>(new ScribbleCore::FunctionReference(*$2, *$4, argTypes, 0));
	ScribbleCore::ParserReference r(reference);
	StatementReferences.push_back(r);
	
	$$ = new ScribbleCore::FunctionReferenceStatement(scribble_lineno, scribble_text, reference);
	
	ScribbleCore::ParserReference q($$);
	StatementReferences.push_back(q);
	
	delete $2;
	delete $4;
	delete $6;
}

/**
 * Defines a functional call as either Name ( Args ) or Package.Name ( Args ).
 */
FunctionCall: WORD LPAREN Arguments RPAREN {

		auto it = findVariable(*$1);
		
		if (it.get() == nullptr) {
			SmartPointer<ScribbleCore::FunctionReference> reference = SmartPointer<ScribbleCore::FunctionReference>(new ScribbleCore::FunctionReference("", *$1, *$3, 0));
			StatementReferences.push_back(reference);
			$$ = new ScribbleCore::FunctionStatement(scribble_lineno, scribble_text, reference, *$3, Variables.size());
		} else {
			ScribbleCore::SafeStatement var = ScribbleCore::SafeStatement(new ScribbleCore::GetVariableStatement(scribble_lineno, scribble_text, it));
			$$ = new ScribbleCore::CallFunctionReference(scribble_lineno, scribble_text, var, *$3, Variables.size());
		}
		
		ScribbleCore::ParserReference r($$);
		StatementReferences.push_back(r);
		
		delete $3;
		delete $1;
		
	} | WORD LINK WORD LPAREN Arguments RPAREN {
	
		SmartPointer<ScribbleCore::FunctionReference> reference = SmartPointer<ScribbleCore::FunctionReference>(new ScribbleCore::FunctionReference(*$1, *$3, *$5, 0));
		StatementReferences.push_back(reference);
	
		$$ = new ScribbleCore::FunctionStatement(scribble_lineno, scribble_text, reference, *$5, Variables.size());
	
		ScribbleCore::ParserReference r($$);
		StatementReferences.push_back(r);		
	
		//Free the name pointers
		delete $1;
		delete $3;
		delete $5;
	};

/**
 * Either a single Statement or many statements inside some curly brackets { }.
 */
IfStatements: Statement {
		std::vector<ScribbleCore::SafeStatement>* stmts = new std::vector<ScribbleCore::SafeStatement>();
		stmts->push_back(ScribbleCore::SafeStatement($1));
		$$ = stmts;
	} | LBRACKET Statements RBRACKET {
		$$ = $2;
	};

/**
 * Defines the options allowed when creating a single expression function (func F() -> int := 5 etc)
 */
GuardOrExpression: IF Guard END {
		$$ = $2;
	} | Expression END {
		$$ = new ScribbleCore::ReturnStatement($1->line(), $1->symbol(), SmartPointer<ScribbleCore::Statement>($1));
	};

/**
 * Definition of a guard (ie. x = 0 -> 0 | otherwise -> 1)
 */
Guard: Expression THEN Expression GUARD Guard {
		std::vector<SmartPointer<ScribbleCore::Statement>> expr;
		std::vector<SmartPointer<ScribbleCore::Statement>> elseexpr;
		SmartPointer<ScribbleCore::Statement> rStmt = SmartPointer<ScribbleCore::Statement>(new ScribbleCore::ReturnStatement($3->line(), $3->symbol(), SmartPointer<ScribbleCore::Statement>($3)));
		SmartPointer<ScribbleCore::Statement> elseRStmt = SmartPointer<ScribbleCore::Statement>($5);
		expr.push_back(rStmt);
		elseexpr.push_back(elseRStmt);
		$$ = new ScribbleCore::IfStatement(scribble_lineno, scribble_text, ScribbleCore::SafeStatement($1), expr, elseexpr);
	} | Expression THEN Expression {
		std::vector<SmartPointer<ScribbleCore::Statement>> expr;
		SmartPointer<ScribbleCore::Statement> rStmt = SmartPointer<ScribbleCore::Statement>(new ScribbleCore::ReturnStatement($3->line(), $3->symbol(), SmartPointer<ScribbleCore::Statement>($3)));
		expr.push_back(rStmt);
		$$ = new ScribbleCore::IfStatement(scribble_lineno, scribble_text, ScribbleCore::SafeStatement($1), expr, std::vector<SmartPointer<ScribbleCore::Statement>>());
	} | ELSE Expression {
		$$ = new ScribbleCore::ReturnStatement($2->line(), $2->symbol(), SmartPointer<ScribbleCore::Statement>($2));
	};

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
	} | FOR Expression END Expression END Expression DO LBRACKET Statements RBRACKET {
		$$ = new ScribbleCore::ForStatement(scribble_lineno, scribble_text, ScribbleCore::SafeStatement($2), ScribbleCore::SafeStatement($4), ScribbleCore::SafeStatement($6), *$9);
		delete $9;
	} | FOR WORD BETWEEN Expression AND Expression DO LBRACKET Statements RBRACKET {
		auto it = findVariable(*$2);

		if (it.get() == nullptr) {
			scribble_error((std::string(*$2) + " is not defined").c_str());
		} else {
			auto start = ScribbleCore::SafeStatement(new ScribbleCore::AssignVariableStatement(scribble_lineno, scribble_text, it, ScribbleCore::SafeStatement($4)));

			auto getVar = ScribbleCore::SafeStatement(new ScribbleCore::GetVariableStatement(scribble_lineno, scribble_text, it));
			

			auto end = ScribbleCore::SafeStatement(new ScribbleCore::TestStatement(scribble_lineno, scribble_text, ScribbleCore::TestLess, getVar, ScribbleCore::SafeStatement($6)));
			
			//The increment step is just +1 on the variable supplied
			auto inc = ScribbleCore::SafeStatement(new ScribbleCore::IncrementStatement(scribble_lineno, scribble_text, it, ScribbleCore::Increment, false));

			$$ = new ScribbleCore::ForStatement(scribble_lineno, scribble_text, start, end, inc, *$9);
		}

		delete $2;
		delete $9;
	} | FOR Variable BETWEEN Expression AND Expression DO LBRACKET Statements RBRACKET {
		auto it = *$2;

		auto start = ScribbleCore::SafeStatement(new ScribbleCore::AssignVariableStatement(scribble_lineno, scribble_text, it, ScribbleCore::SafeStatement($4)));

		auto getVar = ScribbleCore::SafeStatement(new ScribbleCore::GetVariableStatement(scribble_lineno, scribble_text, it));
			

		auto end = ScribbleCore::SafeStatement(new ScribbleCore::TestStatement(scribble_lineno, scribble_text, ScribbleCore::TestLess, getVar, ScribbleCore::SafeStatement($6)));
			
		//The increment step is just +1 on the variable supplied
		auto inc = ScribbleCore::SafeStatement(new ScribbleCore::IncrementStatement(scribble_lineno, scribble_text, it, ScribbleCore::Increment, false));

		$$ = new ScribbleCore::ForStatement(scribble_lineno, scribble_text, start, end, inc, *$9);
		
		delete $2;
		delete $9;
	} | FOR IntVariable BETWEEN Expression AND Expression DO LBRACKET Statements RBRACKET {
		auto it = *$2;

		auto start = ScribbleCore::SafeStatement(new ScribbleCore::AssignVariableStatement(scribble_lineno, scribble_text, it, ScribbleCore::SafeStatement($4)));

		auto getVar = ScribbleCore::SafeStatement(new ScribbleCore::GetVariableStatement(scribble_lineno, scribble_text, it));
			

		auto end = ScribbleCore::SafeStatement(new ScribbleCore::TestStatement(scribble_lineno, scribble_text, ScribbleCore::TestLess, getVar, ScribbleCore::SafeStatement($6)));
			
		//The increment step is just +1 on the variable supplied
		auto inc = ScribbleCore::SafeStatement(new ScribbleCore::IncrementStatement(scribble_lineno, scribble_text, it, ScribbleCore::Increment, false));

		$$ = new ScribbleCore::ForStatement(scribble_lineno, scribble_text, start, end, inc, *$9);
		
		delete $2;
		delete $9;
	} | WHILE Expression DO LBRACKET Statements RBRACKET {
		$$ = new ScribbleCore::WhileStatement(scribble_lineno, scribble_text, ScribbleCore::SafeStatement($2), *$5);
		delete $5;
	} | RETURN Expression END {	
		$$ = new ScribbleCore::ReturnStatement(scribble_lineno, scribble_text, ScribbleCore::SafeStatement($2));	
	} | RETURN END {
		$$ = new ScribbleCore::ReturnStatement(scribble_lineno, scribble_text, nullptr);
	};

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
	} | NIL {
		$$ = new ScribbleCore::NilStatement(scribble_lineno, scribble_text);
	} | STRING {
		$$ = new ScribbleCore::StringStatement(scribble_lineno, scribble_text, *$1);
		delete $1;
	} | NOT Expression {
		$$ = new ScribbleCore::NotStatement(scribble_lineno, scribble_text, ScribbleCore::SafeStatement($2));
	} | FunctionReference {
		$$ = $1;
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
	} | WORD PLUS_ASSIGN Expression {
		auto it = findVariable(*$1);

		if (it.get() == nullptr) {
			scribble_error((std::string(*$1) + " is not defined").c_str());
		} else {
			auto add = ScribbleCore::SafeStatement(
				new ScribbleCore::OperateStatement(
					scribble_lineno,
					scribble_text,
					ScribbleCore::Add,
					ScribbleCore::SafeStatement(new ScribbleCore::GetVariableStatement(scribble_lineno,scribble_text, it)),
					ScribbleCore::SafeStatement($3)
				)
			);
			$$ = new ScribbleCore::AssignVariableStatement(scribble_lineno, scribble_text, it, add);
		}
		delete $1;
	} | WORD MINUS_ASSIGN Expression {
		auto it = findVariable(*$1);

		if (it.get() == nullptr) {
			scribble_error((std::string(*$1) + " is not defined").c_str());
		} else {
			auto add = ScribbleCore::SafeStatement(
				new ScribbleCore::OperateStatement(
					scribble_lineno,
					scribble_text,
					ScribbleCore::Subtract,
					ScribbleCore::SafeStatement(new ScribbleCore::GetVariableStatement(scribble_lineno,scribble_text, it)),
					ScribbleCore::SafeStatement($3)
				)
			);
			$$ = new ScribbleCore::AssignVariableStatement(scribble_lineno, scribble_text, it, add);
		}
		delete $1;
	} | AutoVariable {
		$$ = $1;
	} | Expression TERNARY Expression COLON Expression {
		$$ = new ScribbleCore::TernaryStatement(scribble_lineno, scribble_text, ScribbleCore::SafeStatement($1), ScribbleCore::SafeStatement($3), ScribbleCore::SafeStatement($5));
	} | LENGTH LPAREN Expression RPAREN {
		$$ = new ScribbleCore::ArrayLengthStatement(scribble_lineno, scribble_text, ScribbleCore::SafeStatement($3));
	} | LSQBRACKET Expression RSQBRACKET Type {
		$$ = new ScribbleCore::ArrayStatement(scribble_lineno, scribble_text, ScribbleCore::makeTypeReference(ScribbleCore::getTypeManager().getType(ScribbleCore::Array, *$4)), ScribbleCore::SafeStatement($2));
		delete $4;
	} | Expression LSQBRACKET Expression RSQBRACKET ASSIGN Expression {
		$$ = new ScribbleCore::AssignArrayStatement(scribble_lineno, scribble_text, ScribbleCore::SafeStatement($1), ScribbleCore::SafeStatement($6), ScribbleCore::SafeStatement($3));
	} | Expression LSQBRACKET Expression RSQBRACKET {
		$$ = new ScribbleCore::GetArrayStatement(scribble_lineno, scribble_text, ScribbleCore::SafeStatement($1), ScribbleCore::SafeStatement($3));
		ScribbleCore::ParserReference r($$);
		StatementReferences.push_back(r);
	} | Expression PLUS Expression {
		$$ = new ScribbleCore::OperateStatement(scribble_lineno, scribble_text, ScribbleCore::Add, ScribbleCore::SafeStatement($1), ScribbleCore::SafeStatement($3));
	} | Expression MINUS Expression {
		$$ = new ScribbleCore::OperateStatement(scribble_lineno, scribble_text, ScribbleCore::Subtract, ScribbleCore::SafeStatement($1), ScribbleCore::SafeStatement($3));
	} | Expression TIMES Expression {
		$$ = new ScribbleCore::OperateStatement(scribble_lineno, scribble_text, ScribbleCore::Multiply, ScribbleCore::SafeStatement($1), ScribbleCore::SafeStatement($3));
	} | Expression DIVIDE Expression {
		$$ = new ScribbleCore::OperateStatement(scribble_lineno, scribble_text, ScribbleCore::Divide, ScribbleCore::SafeStatement($1), ScribbleCore::SafeStatement($3));
	} | Expression EQUALS Expression {
		$$ = new ScribbleCore::TestStatement(scribble_lineno, scribble_text, ScribbleCore::TestEquals, ScribbleCore::SafeStatement($1), ScribbleCore::SafeStatement($3));
	} | Expression NOT_EQUAL Expression {
		$$ = new ScribbleCore::TestStatement(scribble_lineno, scribble_text, ScribbleCore::TestNotEquals, ScribbleCore::SafeStatement($1), ScribbleCore::SafeStatement($3));
	} | Expression GREATER Expression {
		$$ = new ScribbleCore::TestStatement(scribble_lineno, scribble_text, ScribbleCore::TestGreater, ScribbleCore::SafeStatement($1), ScribbleCore::SafeStatement($3));
	} | Expression LESSER Expression {
		$$ = new ScribbleCore::TestStatement(scribble_lineno, scribble_text, ScribbleCore::TestLess, ScribbleCore::SafeStatement($1), ScribbleCore::SafeStatement($3));
	} | Expression LESSER_EQUAL Expression {
		$$ = new ScribbleCore::TestStatement(scribble_lineno, scribble_text, ScribbleCore::TestLessOrEqual, ScribbleCore::SafeStatement($1), ScribbleCore::SafeStatement($3));
	} | Expression GREATER_EQUAL Expression {
		$$ = new ScribbleCore::TestStatement(scribble_lineno, scribble_text, ScribbleCore::TestGreaterOrEqual, ScribbleCore::SafeStatement($1), ScribbleCore::SafeStatement($3));
	} | LPAREN Expression RPAREN {
		$$ = $2;
	} | WORD ASSIGN Expression {
		auto it = findVariable(*$1);

		if (it.get() == nullptr) {
			scribble_error((std::string(*$1) + " is not defined").c_str());
		} else {
			$$ = new ScribbleCore::AssignVariableStatement(scribble_lineno, scribble_text, it, ScribbleCore::SafeStatement($3));
		}
		
		delete $1;
	} | Expression CONCAT Expression {
		std::vector<ScribbleCore::SafeStatement> args;
		args.push_back(ScribbleCore::SafeStatement($1));
		args.push_back(ScribbleCore::SafeStatement($3));
	
		SmartPointer<ScribbleCore::FunctionReference> reference = SmartPointer<ScribbleCore::FunctionReference>(new ScribbleCore::FunctionReference("__system", "Concat", args, 0));
	
		ScribbleCore::ParserReference r(reference);
		StatementReferences.push_back(r);
		
		$$ = new ScribbleCore::FunctionStatement(scribble_lineno, scribble_text, reference, args, Variables.size());
	} | WORD INCREMENT {
		auto it = findVariable(*$1);

		if (it.get() == nullptr) {
			scribble_error((std::string(*$1) + " is not defined").c_str());
		} else {
			$$ = new ScribbleCore::IncrementStatement(scribble_lineno, scribble_text, it, ScribbleCore::Increment, false);
		}
		
		delete $1;
	} | INCREMENT WORD {
		auto it = findVariable(*$2);

		if (it.get() == nullptr) {
			scribble_error((std::string(*$2) + " is not defined").c_str());
		} else {
			$$ = new ScribbleCore::IncrementStatement(scribble_lineno, scribble_text, it, ScribbleCore::Increment, true);
		}
		
		delete $2;
	} | WORD DECREMENT {
		auto it = findVariable(*$1);

		if (it.get() == nullptr) {
			scribble_error((std::string(*$1) + " is not defined").c_str());
		} else {
			$$ = new ScribbleCore::IncrementStatement(scribble_lineno, scribble_text, it, ScribbleCore::Decrement, false);
		}
		
		delete $1;
	} | DECREMENT WORD {
		auto it = findVariable(*$2);

		if (it.get() == nullptr) {
			scribble_error((std::string(*$2) + " is not defined").c_str());
		} else {
			$$ = new ScribbleCore::IncrementStatement(scribble_lineno, scribble_text, it, ScribbleCore::Decrement, true);
		}
		
		delete $2;
	} | Expression AND Expression {
		$$ = new ScribbleCore::AndStatement(scribble_lineno, scribble_text, ScribbleCore::SafeStatement($1), ScribbleCore::SafeStatement($3));
	} | Expression OR Expression {
		$$ = new ScribbleCore::OrStatement(scribble_lineno, scribble_text, ScribbleCore::SafeStatement($1), ScribbleCore::SafeStatement($3));
	} | Expression LPAREN Arguments RPAREN {
		$$ = new ScribbleCore::CallFunctionReference(scribble_lineno, scribble_text, ScribbleCore::SafeStatement($1), *$3, Variables.size());

		ScribbleCore::ParserReference r($$);
		StatementReferences.push_back(r);

		delete $3;
	} | Expression POINT WORD {
		$$ = new ScribbleCore::GetStructureElementStatement(scribble_lineno, scribble_text, ScribbleCore::SafeStatement($1), *$3);
		
		ScribbleCore::ParserReference r($$);
		StatementReferences.push_back(r);
		
		delete $3;
	} | Expression POINT WORD ASSIGN Expression {
		$$ = new ScribbleCore::StructureAssignElement(scribble_lineno, scribble_text, ScribbleCore::SafeStatement($1), ScribbleCore::SafeStatement($5), *$3);
		
		ScribbleCore::ParserReference r($$);
		StatementReferences.push_back(r);
	
		delete $3;
	} | FunctionCall {
		$$ = $1;
	} | WORD {
		auto it = findVariable(*$1);

		if (it.get() == nullptr) {
			scribble_error((std::string("Variable '") + std::string(*$1) + "' is not defined").c_str());
			return -1;
		} else {
			$$ = new ScribbleCore::GetVariableStatement(scribble_lineno, scribble_text, it);
		}

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

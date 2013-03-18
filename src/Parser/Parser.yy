%error-verbose
%locations

%{
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <Statement/IntStatement.hpp>
#include <Statement/OperateStatement.hpp>
#include <Statement/StringStatement.hpp>
#include <Statement/AssignVariable.hpp>
#include <Statement/GetVariableStatement.hpp>
#include <Statement/FunctionStatement.hpp>
#include <Statement/ForStatement.hpp>
#include <Statement/TestStatement.hpp>
#include <Statement/IfStatement.hpp>
#include <Statement/OperateStatement.hpp>
#include <Statement/ReturnStatement.hpp>
#include <Pointers/SmartPointer.hpp>
#include <Function/Function.hpp>
#include <Function/ScriptedFunction.hpp>
#include <Function/WriteFunction.hpp>

#include <Value/Variable.hpp>
#include <Value/String.hpp>

int yylex();
void yyerror(const char* s);

bool ParsingError;
std::map<std::string, Variable*> Variables;
std::map<std::string, SmartPointer<Function>> Functions;
std::vector<SmartPointer<FunctionReference>> References;

extern int yylineno;	// defined and maintained in lex.c
extern char *yytext;	// defined and maintained in lex.c

%}

%union {
	std::string* string;
	std::vector<SmartPointer<Statement>>* statements;
	std::vector<SmartPointer<Variable>>* variables;
	Statement* statement;
	Function* function;
	Variable* variable;
	float real;
	int integer;
	ValueType type;
}

%token <string> WORD STRING
%token <real> REAL
%token <integer> INT
%token <token> PLUS MINUS TIMES DIVIDE POWER EQUALS ASSIGN IF ELSE GREATER LESSER FOR TYPE_VOID RETURN
%token <token> LPAREN RPAREN LBRACKET RBRACKET COMMA
%token <token> FUNCTION VARIABLE CONST STRUCT
%token <token> TYPE_INT TYPE_STRING COLON
%token <token> END

%left PLUS MINUS
%left TIMES DIVIDE
%left NEG
%right POWER

%type <statement> Statement;
%type <statements> Program;
%type <variable> Variable;
%type <statements> Arguments;
%type <statements> Statements;
%type <function> Function;
%type <variables> Variables;
%type <type> Type;

%start Program
%%

Program: { 
		Variables.clear();
		$$ = 0;
	} | Program Function {
		$$ = $1;
	}
;

Type: TYPE_INT {
		$$ = Int;
	} | TYPE_STRING {
		$$ = String;
	} | TYPE_VOID {
		$$ = Void;
	}
;

Variable:  VARIABLE WORD COLON TYPE_INT {

		auto it = Variables.find(*$2);
		
		if (it != Variables.end()) {
			yyerror("Variable already defined");
			return -1;
		} else {
			Variable* nVar = new Variable(Int, new IntValue(0));
			Variables[*$2] = nVar;
			$$ = nVar;
		}
		
	} | VARIABLE WORD COLON TYPE_STRING {
		auto it = Variables.find(*$2);
		if (it != Variables.end()) {
			yyerror("Variable already defined");
			return -1;
		} else {
			Variable* nVar = new Variable(String, new StringValue(""));
			Variables[*$2] = nVar;
			$$ = nVar;
		}
	}
;

Variables: Variable {
		$$ = new std::vector<SP<Variable>>();
		$$->push_back($1);
	} | Variables COMMA Variable {
		$$ = $1;
		$$->push_back($3);
	}
;

Function: FUNCTION WORD LPAREN Variables RPAREN COLON Type LBRACKET Statements RBRACKET {
	$$ = new ScriptedFunction($7, *$9, *$4);
	Functions[*$2] = $$;
	} | FUNCTION WORD LPAREN RPAREN COLON Type LBRACKET Statements RBRACKET {
	$$ = new ScriptedFunction($6, *$8, std::vector<SP<Variable>>());
	Functions[*$2] = $$;
	}
;

Arguments: Statement {
		$$ = new std::vector<SmartPointer<Statement>>();
		$$->push_back($1);
	} | Arguments COMMA Statement {
		$$ = $1;
		$$->push_back($3);
	}
;

Statements: {
		$$ = new std::vector<SmartPointer<Statement>>();
	} | Statements Statement {
		$$ = $1;
		$$->push_back($2);
	} | Statements RETURN Statement {
		$$ = $1;
		$$->push_back(new ReturnStatement(yylineno, yytext, $3));
	}
;


Statement: INT {
		$$ = new IntStatement(yylineno, yytext, $1);
	} | STRING {
		$$ = new StringStatement(yylineno, yytext, *$1);
	} | Variable {
		$$ = new GetVariableStatement(yylineno, yytext, $1);
	} | Variable ASSIGN Statement {
		$$ = new AssignVariableStatement(yylineno, yytext, $1, $3);
	} | WORD {

		auto it = Variables.find(*$1);

		if (it == Variables.end()) {
			yyerror("Variable not defined");
			return -1;
		} else {
			$$ = new GetVariableStatement(yylineno, yytext, it->second);
		}

	} | IF Statement LBRACKET Statements RBRACKET {
		$$ = new IfStatement(yylineno, yytext, $2, *$4, std::vector<SP<Statement>>());
	} | IF Statement LBRACKET Statements RBRACKET ELSE LBRACKET Statements RBRACKET {
		$$ = new IfStatement(yylineno, yytext, $2, *$4, *$8);
	} | Statement PLUS Statement {
		$$ = new OperateStatement(yylineno, yytext, Add, $1, $3);
	} | Statement MINUS Statement {
		$$ = new OperateStatement(yylineno, yytext, Subtract, $1, $3);
	} | Statement TIMES Statement {
		$$ = new OperateStatement(yylineno, yytext, Multiply, $1, $3);
	} | FOR Statement END Statement END Statement LBRACKET Statements RBRACKET {
		$$ = new ForStatement(yylineno, yytext, $2, $4, $6, *$8);
	} | WORD LPAREN Arguments RPAREN {
	
		std::vector<SmartPointer<Statement>> args;

		for (unsigned int i = 0; i < $3->size(); ++i) {
			args.push_back($3->at(i));
		}

		delete $3;
		
		SmartPointer<FunctionReference> reference = SmartPointer<FunctionReference>(new FunctionReference(*$1, 0));
		References.push_back(reference);
		$$ = new FunctionStatement(yylineno, yytext, reference, args);
	} | Statement EQUALS Statement {
		$$ = new TestStatement(yylineno, yytext, TestEquals, $1, $3);
	}  | Statement GREATER Statement {
		$$ = new TestStatement(yylineno, yytext, TestGreater, $1, $3);
	}  | Statement LESSER Statement {
		$$ = new TestStatement(yylineno, yytext, TestLess, $1, $3);
	} | TYPE_STRING LPAREN Arguments RPAREN {
	
		//Copy arguments over
		std::vector<SmartPointer<Statement>> args;

		for (unsigned int i = 0; i < $3->size(); ++i) {
			args.push_back($3->at(i));
		}

		delete $3;
		
		SmartPointer<FunctionReference> reference = SmartPointer<FunctionReference>(new FunctionReference("string", 0));
		References.push_back(reference);
		$$ = new FunctionStatement(yylineno, yytext, reference, args);
	} | LPAREN Statement RPAREN {
		$$ = $2;
	} | WORD ASSIGN Statement {
		auto it = Variables.find(*$1);

		if (it == Variables.end()) {
			yyerror("Variable not defined");
		} else {
			$$ = new AssignVariableStatement(yylineno, yytext, it->second, $3);
		}
	}
;

%%

void yyerror(std::string s)
{

  printf("ERROR: %s at symbol %s on line %i\n", s.c_str(), yytext, yylineno);
  ParsingError = true;
}

void yyerror(const char* s)
{
  yyerror(std::string(s));
}

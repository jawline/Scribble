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
#include <Statement/StringStatement.hpp>
#include <Statement/AssignVariable.hpp>
#include <Statement/GetVariableStatement.hpp>
#include <Statement/FunctionStatement.hpp>
#include <Pointers/SmartPointer.hpp>
#include <Function/Function.hpp>
#include <Function/WriteFunction.hpp>

#include <Value/Variable.hpp>

int yylex();
void yyerror(const char* s);
std::vector<SmartPointer<Statement>>* Statements;
std::map<std::string, Variable*> Variables;

%}

%union {
	std::string* string;
	std::vector<SmartPointer<Statement>>* statements;
	Statement* statement;
	float real;
	int integer;
}

%token <string> WORD STRING
%token <real> REAL
%token <integer> INT
%token <token> PLUS MINUS TIMES DIVIDE POWER EQUALS ASSIGN
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
%type <statement> Declaration;
%type <void> Structure;
%type <statement> Variable;
%type <statements> Arguments;

%start Program
%%

Program: { 
		Statements = new std::vector<SmartPointer<Statement>>();
		Variables.clear();
		$$ = Statements; 
	} | Program Declaration {
	} | Program Statement END {
		$1->push_back($2);
		$$ = $1; 
	}
;

Structure: STRUCT WORD LBRACKET Declarations RBRACKET { printf("Structure %s\n", $2->c_str()); }

Declarations: { }
	| Declarations Declaration { }
;

Declaration: Variable END { }
	| Structure { }
;

Variable:  VARIABLE WORD COLON TYPE_INT {
		std::map<std::string, Variable*>::iterator it;

		it = Variables.find(*$2);

		if (it != Variables.end()) {
			yyerror("Variable already defined");
			return -1;
		} else {
			Variables[*$2] = new Variable(Int);
		}
	} | VARIABLE WORD COLON TYPE_STRING {
		std::map<std::string, Variable*>::iterator it;
		it = Variables.find(*$2);
		if (it != Variables.end()) {
			yyerror("Variable already defined");
			return -1;
		} else {
			Variables[*$2] = new Variable(String);
		}
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

Statement: INT {
		$$ = new IntStatement($1);
	} | STRING {
		$$ = new StringStatement(*$1);
	} | WORD {

	std::map<std::string, Variable*>::iterator it;

		it = Variables.find(*$1);

		if (it == Variables.end()) {
			yyerror("Variable not defined");
			return -1;
		} else {
			$$ = new GetVariableStatement(it->second);
		}

	} | WORD LPAREN Arguments RPAREN {
		std::vector<SmartPointer<Statement>> args;

		for (unsigned int i = 0; i < $3->size(); ++i) {
			args.push_back($3->at(i));
		}

		delete $3;

		$$ = new FunctionStatement( SmartPointer<Function>(new WriteFunction()) , args);
	} | LPAREN Statement RPAREN {
		$$ = $2;
	} | WORD ASSIGN Statement {
		std::map<std::string, Variable*>::iterator it;

		it = Variables.find(*$1);

		if (it == Variables.end()) {
			yyerror("Variable not defined");
		} else {
			$$ = new AssignVariableStatement(it->second, $3);
		}
	}
;

%%

void yyerror(std::string s)
{
  extern int yylineno;	// defined and maintained in lex.c
  extern char *yytext;	// defined and maintained in lex.c

  printf("ERROR: %s at symbol %s on line %i\n", s.c_str(), yytext, yylineno);
}

void yyerror(const char* s)
{
  yyerror(std::string(s));
}

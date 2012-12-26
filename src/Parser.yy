%error-verbose
%{
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <Statement/IntStatement.hpp>
#include <Statement/FloatStatement.hpp>
#include <Statement/AddStatement.hpp>
#include <Statement/StringStatement.hpp>
#include <Statement/LoadVariable.hpp>
#include <Statement/StoreVariable.hpp>
#include <Statement/AssignVariable.hpp>
#include <Value/Value.hpp>

int yylex();
void yyerror(const char* s);
std::vector<Statement*>* Statements;
std::map<std::string, int> Variables;
int VariableCount;
typedef std::pair<std::string, int> VariableDefinition;

%}

%union {
	std::string* string;
	std::vector<Statement*>* statements;
	Statement* statement;
	float real;
	int integer;
}

%token <string> WORD STRING
%token <real> REAL
%token <integer> INT
%token <token> PLUS MINUS TIMES DIVIDE POWER EQUALS
%token <token> LPAREN RPAREN LBRACKET RBRACKET COMMA
%token <token> FUNCTION VARIABLE CONST
%token <token> END

%left PLUS MINUS
%left TIMES DIVIDE
%left NEG
%right POWER

%type <statement> Statement;
%type <statements> Program;
%type <statement> Declaration;

%start Program
%%

Program: { 
		Statements = new std::vector<Statement*>();
		Variables.clear();
		VariableCount = 0;
		$$ = Statements; 
	} | Program Declaration END {
		if ($2 != NULL) {
			$1->push_back($2);
		}
		$$ = $1; 
	} | Program Statement END {
		$1->push_back($2);
		$$ = $1; 
	}
;

Declaration: VARIABLE WORD {

		if (Variables.find(*$2) == Variables.end()) {
			Variables.insert(VariableDefinition(*$2, VariableCount++));
		} else {
			yyerror("Variable already defined");
			return -1;
		}

		$$ = NULL;
	}
	| VARIABLE WORD EQUALS Statement {

		if (Variables.find(*$2) == Variables.end()) {
			Variables.insert(VariableDefinition(*$2, VariableCount++));
		} else {
			yyerror("Variable already defined");
			return -1;
		}

		$$ = new AssignVariableStatement(Variables.find(*$2)->second, $4);
	}
;

Statement: REAL {
		$$ = new FloatStatement($1);
	} | INT {
		$$ = new IntStatement($1);
	} | STRING {
		$$ = new StringStatement(*$1);
	} | WORD {

		if (Variables.find(*$1) != Variables.end()) {
			$$ = new LoadVariableStatement(Variables.find(*$1)->second);
		} else {
			printf("%s\n", $1->c_str());
			yyerror("Error variable not defined");
			return -1;
		}

	} | LPAREN Statement RPAREN {
		$$ = $2;
	} | Statement PLUS Statement {
		$$ = new AddStatement($1, $3);
	} | Statement MINUS Statement {
		$$ = $1;
	} | WORD EQUALS Statement {

		if (Variables.find(*$1) != Variables.end()) {
			$$ = new AssignVariableStatement(Variables.find(*$1)->second, $3);
		} else {
			printf("%s\n", $1->c_str());
			yyerror("Error variable not defined");
			return -1;
		}		

	} | Statement TIMES Statement {
		$$ = $1;
	} | Statement DIVIDE Statement {
		$$ = $1;
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

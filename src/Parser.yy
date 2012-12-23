%error-verbose
%{
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <Statement/IntStatement.hpp>
#include <Statement/FloatStatement.hpp>
#include <Statement/AddStatement.hpp>
#include <Statement/StringStatement.hpp>
#include <Value/Value.hpp>

extern int yylex();
extern FILE* yyin;
void yyerror(const char *s) { printf("ERROR: %s\n", s); }
std::vector<std::string*>* Statements;

%}

%union {
	std::string* string;
	std::vector<std::string*>* strings;
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

%type <statement> Statement 
%type <strings> Program
%type <statement> Declaration;

%start Program
%%

Program: { Statements = new std::vector<std::string*>(); $$ = Statements; }
	| Program Declaration END { $$ = $1; }
	| Program Statement END { printf("Statement: %s", ($2)->GenerateBytecode().c_str()); $$=$1; }
;

Declaration: VARIABLE WORD { printf("New variable %s\n", $2->c_str()); $$ = NULL; }
	| Declaration EQUALS Statement { printf("Assign new variable to %s", $3->GenerateBytecode().c_str()); $$ = NULL; }
;

Statement: REAL { $$ = new FloatStatement($1); }
	| INT { $$ = new IntStatement($1); }
	| STRING { $$ = new StringStatement(*$1); }
	| LPAREN Statement RPAREN { $$ = $2; }
	| Statement PLUS Statement { $$ = new AddStatement($1, $3); }
	| Statement MINUS Statement { $$ = $1;}
	| WORD EQUALS Statement { $$ = $3;}
	| Statement TIMES Statement {  $$ = $1; }
	| Statement DIVIDE Statement { $$ = $1;}
;

%%

/**
int main() {
	// open a file handle to a particular file:
	FILE *myfile = fopen("test.scribble", "r");

	// make sure it's valid:
	if (!myfile) {
		printf("unable to open input\n");
		return -1;
	}

	// set lex to read from it instead of defaulting to STDIN:
	yyin = myfile;
	
	// lex through the input:
	yyparse();
}
*/

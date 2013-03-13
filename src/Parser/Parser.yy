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
#include <Statement/ForStatement.hpp>
#include <Statement/TestStatement.hpp>
#include <Statement/IfStatement.hpp>
#include <Statement/AddStatement.hpp>
#include <Pointers/SmartPointer.hpp>
#include <Function/Function.hpp>
#include <Function/WriteFunction.hpp>

#include <Value/Variable.hpp>
#include <Value/String.hpp>

int yylex();
void yyerror(const char* s);

bool ParsingError;
std::vector<SmartPointer<Statement>>* Statements;
std::map<std::string, Variable*> Variables;
std::map<std::string, SmartPointer<Function>> Functions;

%}

%union {
	std::string* string;
	std::vector<SmartPointer<Statement>>* statements;
	Statement* statement;
	Variable* variable;
	float real;
	int integer;
}

%token <string> WORD STRING
%token <real> REAL
%token <integer> INT
%token <token> PLUS MINUS TIMES DIVIDE POWER EQUALS ASSIGN IF ELSE GREATER LESSER FOR
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

%start Program
%%

Program: { 
		Statements = new std::vector<SmartPointer<Statement>>();
		Variables.clear();
		$$ = Statements; 
	} | Program Variable {
	} | Program Variable ASSIGN Statement {
		
		if ($2->getType() != $4->type()) {
			yyerror("Invalid type");
			return -1;
		}
		
		Statement* assign = new AssignVariableStatement($2, $4);
		$1->push_back(assign);
		$$ = $1;
	} | Program Statement {
		$1->push_back($2);
		$$ = $1; 
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
	}
;


Statement: INT {
		$$ = new IntStatement($1);
	} | STRING {
		$$ = new StringStatement(*$1);
	} | WORD {

		auto it = Variables.find(*$1);

		if (it == Variables.end()) {
			yyerror("Variable not defined");
			return -1;
		} else {
			$$ = new GetVariableStatement(it->second);
		}

	} | IF Statement LBRACKET Statements RBRACKET {
		
		if ($2->type() != Boolean) {
			yyerror("Statement is not a bool");
			return -1;
		}
		
		$$ = new IfStatement($2, *$4, std::vector<SP<Statement>>());
	} | IF Statement LBRACKET Statements RBRACKET ELSE LBRACKET Statements RBRACKET {
	
		if ($2->type() != Boolean) {
			yyerror("Statement is not a bool");
			return -1;
		}
	
		$$ = new IfStatement($2, *$4, *$8);
	} | Statement PLUS Statement {
	
		if ($1->type() != $3->type()) {
			yyerror("Cannot add values of different types");
			return -1;
		}
	
		$$ = new AddStatement($1, $3);
	} | FOR Statement END Statement END Statement LBRACKET Statements RBRACKET {
	
		if ($4->type() != Boolean) {
			yyerror("Statement is not a bool");
			return -1;
		}
		
		$$ = new ForStatement($2, $4, $6, *$8);
	} | WORD LPAREN Arguments RPAREN {
		std::vector<SmartPointer<Statement>> args;

		for (unsigned int i = 0; i < $3->size(); ++i) {
			args.push_back($3->at(i));
		}

		delete $3;
		
		auto it = Functions.find(*$1);

		if (it == Functions.end()) {
			yyerror("Function does not exist");
		} else {
		
			//Check the number of arguments
			if (args.size() != it->second->numArgs()) {
				yyerror("Incorrect number of arguments");
				return -1;
			}
		
			//Check that they are valid
			for (unsigned int i = 0; i < args.size(); ++i) {
				
				if (args[i]->type() != it->second->argType(i)) {
					yyerror("Unexpected argument type");
					return -1;
				}
				
			}
		
			$$ = new FunctionStatement( it->second, args);
		}
		
	} | Statement EQUALS Statement {
	
		if ($1->type() != $3->type()) {
			yyerror("Error, cannot compare two different types");
			return -1;
		}
	
		$$ = new TestStatement(TestEquals, $1, $3);
	}  | Statement GREATER Statement {
	
		if ($1->type() != $3->type()) {
			yyerror("Error, cannot compare two different types");
			return -1;
		}
	
		$$ = new TestStatement(TestGreater, $1, $3);
	}  | Statement LESSER Statement {
	
		if ($1->type() != $3->type()) {
			yyerror("Error, cannot compare two different types");
			return -1;
		}
	
		$$ = new TestStatement(TestLess, $1, $3);
	} | TYPE_STRING LPAREN Arguments RPAREN {
	
		//Copy arguments over
		std::vector<SmartPointer<Statement>> args;

		for (unsigned int i = 0; i < $3->size(); ++i) {
			args.push_back($3->at(i));
		}

		delete $3;
		
		auto it = Functions.find("string");

		if (it == Functions.end()) {
			yyerror("Function does not exist");
		} else {
		
			//Check the number of arguments
			if (args.size() != it->second->numArgs()) {
				yyerror("Incorrect number of arguments");
				return -1;
			}
		
			//Check that they are valid
			for (unsigned int i = 0; i < args.size(); ++i) {
				
			}
		
			$$ = new FunctionStatement( it->second, args);
		}
		
	} | LPAREN Statement RPAREN {
		$$ = $2;
	} | WORD ASSIGN Statement {
		auto it = Variables.find(*$1);

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
  ParsingError = true;
}

void yyerror(const char* s)
{
  yyerror(std::string(s));
}

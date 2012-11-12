%{
#include <string>
#include <vector>
#include <Pointers/SmartPointer.hpp>
#include <Statement/IntStatement.hpp>
#include <Statement/FloatStatement.hpp>
#include "Parser.hpp"
#include <stdlib.h>

#define SAVE_INT yylval.integer = atoi(yytext);
#define SAVE_REAL yylval.real = atof(yytext);
#define SAVE_TOKEN yylval.string = new SmartPointer<std::string>(new std::string(yytext, yyleng))

extern "C" int yywrap() { }
%}

white [ \t]+
digit [0-9]
integer {digit}+
exponent [eE][+-]?{integer}
real {integer}("."{integer})
string \"[^\"\n]*\"
word [a-z|A-Z][a-z|A-Z|0-9]*

%%

{white} { }
"+" return PLUS;
"-" return MINUS;
"*" return TIMES;
"/" return DIVIDE;
"^" return POWER;
"=" return EQUALS;
"(" return LPAREN;
")" return RPAREN;
"{" return LBRACKET;
"}" return RBRACKET;
"," return COMMA;
";" return END;
"function" return FUNCTION;
"var" return VARIABLE;
"const" return CONST;

{integer} { SAVE_INT;
 return INT;
}

{real} { SAVE_REAL; 
 return REAL;
}

{word} { SAVE_TOKEN; return WORD; }
{string} { SAVE_TOKEN; return STRING; }

%option yylineno
%option noyywrap

%{
#include <string>
#include <vector>
#include <Statement/IntStatement.hpp>
#include <Pointers/SmartPointer.hpp>
#include <Value/Variable.hpp>
#include "Parser.hpp"

#define SAVE_INT yylval.integer = atoi(yytext);
#define SAVE_REAL yylval.real = atof(yytext);
#define SAVE_TOKEN yylval.string = new std::string(yytext, yyleng);

%}

white [ \t]+
digit [0-9]
integer {digit}+
exponent [eE][+-]?{integer}
real {integer}("."{integer})
string \"[^\"\n]*\"
word [_|a-z|A-Z][a-z|A-Z|0-9]*

%%

{white} { }
"+" return PLUS;
"-" return MINUS;
"*" return TIMES;
"/" return DIVIDE;
"^" return POWER;
"=" return EQUALS;
":=" return ASSIGN;
"(" return LPAREN;
")" return RPAREN;
"{" return LBRACKET;
"}" return RBRACKET;
"," return COMMA;
";" return END;
":" return COLON;
">" return GREATER;
"<" return LESSER;
"\n" ;;
"if" return IF;
"else" return ELSE;
"struct" return STRUCT;
"function" return FUNCTION;
"var" return VARIABLE;
"const" return CONST;
"int" return TYPE_INT;
"string" return TYPE_STRING;

{integer} { SAVE_INT;
 return INT;
}

{real} { SAVE_REAL; 
 return REAL;
}

{word} { SAVE_TOKEN; return WORD; }
{string} { SAVE_TOKEN; return STRING; }

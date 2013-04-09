%option yylineno
%option noyywrap
%option nounput

%x C_COMMENT

%{
#include <Function/Function.hpp>
#include <string>
#include <vector>
#include <Statement/IntStatement.hpp>
#include <Pointers/SmartPointer.hpp>
#include <Value/Variable.hpp>
#include "Parser.hpp"

#define SAVE_INT yylval.integer = atoi(yytext);
#define SAVE_REAL yylval.real = atof(yytext);
#define SAVE_TOKEN yylval.string = new std::string(yytext, yyleng);

void myReplace(std::string& str, const std::string& oldStr, const std::string& newStr)
{
  size_t pos = 0;
  while((pos = str.find(oldStr, pos)) != std::string::npos)
  {
     str.replace(pos, oldStr.length(), newStr);
     pos += newStr.length();
  }
}

%}

white [ \t]+
digit [0-9]
integer {digit}+
exponent [eE][+-]?{integer}
real {integer}("."{integer})
string \"[^\"\n]*\"
word [_|a-z|A-Z][a-z|A-Z|0-9]*

%%

"//"            { BEGIN(C_COMMENT); }
<C_COMMENT>"\n" { BEGIN(INITIAL); }
<C_COMMENT>.    { }
{white} { }
"++" return TWOPLUS;
"+" return PLUS;
"--" return TWOMINUS;
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
"!" return NOT;
"\n" ;;
"if" return IF;
"else" return ELSE;
"struct" return STRUCT;
"func" return FUNCTION;
"for" return FOR;
"var" return VARIABLE;
"const" return CONST;
"int" return TYPE_INT;
"bool" return TYPE_BOOL;
"string" return TYPE_STRING;
"void" return TYPE_VOID;
"return" return RETURN;
"while" return WHILE;
"import" return IMPORT;
"true" return TRUE;
"false" return FALSE;
"auto" return AUTO;
"." return LINK;

{integer} { SAVE_INT;
 return INT;
}

{real} { SAVE_REAL; 
 return REAL;
}

{word} { SAVE_TOKEN; return WORD; }
{string} { std::string r(yytext, yyleng); myReplace(r, "\\n", "\n"); myReplace(r, "\"", ""); yylval.string = new std::string(r); return STRING; }

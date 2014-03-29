%option yylineno
%option noyywrap
%option nounput
%option prefix="scribble_"

%x C_COMMENT
%x C_LONG_COMMENT

%{
#include <API/Function.hpp>
#include <string>
#include <vector>
#include <Scribble/Statement/IntStatement.hpp>
#include <Pointers/SmartPointer.hpp>
#include <Scribble/Value/Variable.hpp>
#include <Scribble/Value/StructureInfo.hpp>
#include <Scribble/Parser/TypeReference.hpp>
#include "ScribbleParser.hpp"

#define SAVE_INT scribble_lval.integer = atoi(scribble_text);
#define SAVE_FLOAT scribble_lval.float32 = atof(scribble_text);
#define SAVE_TOKEN scribble_lval.string = new std::string(scribble_text, scribble_leng);

void stringReplace(std::string& str, const std::string& oldStr, const std::string& newStr)
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
real {integer}("."{integer})*
float {real}f
string \"[^\"\n]*\"
word [_|a-z|A-Z][a-z|A-Z|0-9|_]*

%%

"//"            { BEGIN(C_COMMENT); }
<C_COMMENT>"\n" { BEGIN(INITIAL); }
<C_COMMENT>.    { }

"/*" { BEGIN(C_LONG_COMMENT); }
<C_LONG_COMMENT>"*/" { BEGIN(INITIAL); }
<C_LONG_COMMENT>"\n" {}
<C_LONG_COMMENT>. {}

{white} { }

"++" return INCREMENT;
"--" return DECREMENT;

"->" return POINT;
"." return LINK;

"+" return PLUS;
"-" return MINUS;
"*" return TIMES;
"/" return DIVIDE;
"$" return CONCAT;

":=" return ASSIGN;
"=" return EQUALS;

"?" return TERNARY;

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
"[" return LSQBRACKET;
"]" return RSQBRACKET;

"\n" ;


"and" return AND;
"or" return OR;
"package" return PACKAGE;
"then" return THEN;
"if" return IF;
"else" return ELSE;
"struct" return STRUCT;
"func" return FUNCTION;
"for" return FOR;
"var" return VARIABLE;
"int" return TYPE_INT;
"bool" return TYPE_BOOL;
"float32" return TYPE_FLOAT32;
"nil" return NIL;
"string" return TYPE_STRING;
"return" return RETURN;
"while" return WHILE;
"import" return IMPORT;
"true" return TRUE;
"false" return FALSE;
"type" return TYPE;
"do" return DO;
"array" return TYPE_ARRAY;
"len" return LENGTH;
"is" return IS;

{integer} { SAVE_INT;
 return INT;
}

{float} { SAVE_FLOAT; 
 return FLOAT32;
}

{word} { SAVE_TOKEN; return WORD; }
{string} { std::string r(scribble_text, scribble_leng); stringReplace(r, "\\n", "\n"); stringReplace(r, "\"", ""); 
		   scribble_lval.string = new std::string(r); return STRING; }

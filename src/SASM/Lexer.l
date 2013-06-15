%option yylineno
%option noyywrap
%option nounput
%option prefix="sasm_"

%x C_COMMENT

%{
#include <string>
#include "SASMParser.hpp"

#define SAVE_INT sasm_lval.integer = atoi(sasm_text);
#define SAVE_REAL sasm_lval.real = atof(sasm_text);
#define SAVE_TOKEN sasm_lval.string = new std::string(sasm_text, sasm_leng);

void replaceString(std::string& str, const std::string& oldStr, const std::string& newStr)
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
long {integer}L
exponent [eE][+-]?{integer}
real {integer}("."{integer})
string \"[^\"\n]*\"
word [_|a-z|A-Z][a-z|A-Z|0-9]*

%%

"#"            { BEGIN(C_COMMENT); }
<C_COMMENT>"\n" { BEGIN(INITIAL); }
<C_COMMENT>.    { }
{white} { }

"\n" ;
"$" return REG;
"load" return LOAD;
"add" return ADD;
"move" return MOVE;
"push" return PUSH;
"pop" return POP;
"tneq" return TEST_NOT_EQUAL;
"teq" return TEST_EQUAL;
"ret" return RETURN;
"jump" return JUMP;

{integer} { SAVE_INT;
 return INT;
}

{real} { SAVE_REAL; 
 return REAL;
}

{long} { sasm_lval.lval = atoi(sasm_text); return LONG; }

{word} { SAVE_TOKEN; return WORD; }
{string} { std::string r(sasm_text, sasm_leng); replaceString(r, "\\n", "\n"); replaceString(r, "\"", ""); sasm_lval.string = new std::string(r); return STRING; }

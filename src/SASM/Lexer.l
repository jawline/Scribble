%option yylineno
%option noyywrap
%option nounput
%option prefix="sasm_"

%x C_COMMENT

%{
#include <string>
#include "SASMParser.hpp"

#define SAVE_INT sasm_lval.integer = atoi(sasm_text);
#define SAVE_REG sasm_lval.integer = atoi(sasm_text+1);
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
integer -?{digit}+
long {integer}L
real {integer}("."{integer})
register ${integer}
string \"[^\"]*\"
word [_|a-z|A-Z][a-z|A-Z|0-9]*

%%

"#"            { BEGIN(C_COMMENT); }
<C_COMMENT>"\n" { BEGIN(INITIAL); }
<C_COMMENT>.    { }
{white} { }

"\n" ;
"load" return LOAD;
"add" return ADD;
"sub" return SUBTRACT;
"mul" return MULTIPLY;
"div" return DIVIDE;
"call" return CALL_FN;
"move" return MOVE;
"popn" return POP_NIL;
"neq" return TEST_NOT_EQUAL;
"eq" return TEST_EQUAL;
"eqz" return TEST_EQUAL_NIL;
"lt" return LESS_THAN;
"le" return LESS_THAN_OR_EQUAL;
"gt" return GREATER_THAN;
"ge" return GREATER_THAN_OR_EQUAL;
"ret" return RETURN;
"jmp" return JUMP;
"jmpr" return JUMP_RELATIVE;
"newarray" return NEW_ARRAY;
"aset" return ARRAY_SET;
"aget" return ARRAY_GET;
"alen" return ARRAY_LENGTH;
"pushr" return PUSH_REGISTERS;
"popr" return POP_REGISTERS;

{register} {
	SAVE_REG;
	return REG;
}

{integer} { SAVE_INT;
 return INT;
}

{real} { SAVE_REAL; 
 return REAL;
}

{long} { sasm_lval.lval = atoi(sasm_text); return LONG; }

{word} { SAVE_TOKEN; return WORD; }
{string} { std::string r(sasm_text, sasm_leng); replaceString(r, "\\n", "\n"); replaceString(r, "\"", ""); sasm_lval.string = new std::string(r); return STRING; }

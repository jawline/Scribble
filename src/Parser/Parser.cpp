#include "Parser.hpp"
#include <Pointers/SmartPointer.hpp>
#include <Function/ScriptedFunction.hpp>
#include <string.h>

extern std::vector<SmartPointer<Statement>>* Statements;
extern std::map<std::string, int> Variables;
extern void yyparse();
extern void yy_scan_string(char const*);
extern void yylex_destroy();

Function* Parser::generateProgram(std::string inputSource) {

	char* a = strdup(inputSource.c_str());

	yy_scan_string(a);

	yyparse();

	yylex_destroy();

	delete[] a;

	Function* f = new ScriptedFunction(*Statements);

	delete Statements;

	return f;
}

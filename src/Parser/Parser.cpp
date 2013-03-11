#include "Parser.hpp"
#include <Function/ScriptedFunction.hpp>
#include <string.h>

extern std::vector<SmartPointer<Statement>>* Statements;
extern std::map<std::string, SmartPointer<Function>> Functions;
extern bool ParsingError;
extern void yyparse();
extern void yy_scan_string(char const*);
extern void yylex_destroy();

Function* Parser::generateProgram(std::string inputSource,
		std::map<std::string, SmartPointer<Function>> functions) {

	//Copy over builtin functions to functions map
	Functions.empty();

	for (auto it = functions.begin(); it != functions.end(); it++) {
		Functions[it->first] = it->second;
	}

	//Clear and previous errors
	ParsingError = false;

	//Copy the source to the Parser
	char* a = strdup(inputSource.c_str());
	yy_scan_string(a);
	yyparse();
	yylex_destroy();
	delete[] a;

	//Check whether an error has occurred
	if (!ParsingError) {

		//If it hasn't return the source as a function
		Function* f = new ScriptedFunction(*Statements);
		delete Statements;
		return f;
	} else {
		return 0;
	}
}

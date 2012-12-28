#include "Parser.hpp"
#include <string.h>

extern std::vector<Statement*>* Statements;
extern std::map<std::string, int> Variables;
extern void yyparse();
extern void yy_scan_string(char const*);
extern void yylex_destroy();

std::string Parser::generateAssembly(std::string inputSource) {

	char* a = strdup(inputSource.c_str());

	yy_scan_string(a);

	yyparse();

	yylex_destroy();

	delete[] a;

	std::string resultAssembly = "";

	std::map<std::string, int>::iterator i;
	for (i = Variables.begin(); i != Variables.end(); ++i) {
		std::stringstream ss;
		ss << ";Variable ";
		ss << i->first;
		ss << "->";
		ss << i->second;
		ss << "\n";
		resultAssembly += ss.str();
	}

	for (int i = 0; i < Statements->size(); ++i) {

		resultAssembly += Statements->at(i)->GenerateBytecode();

		if (i < Statements->size() - 1) {
				resultAssembly += "\n";
		}

	}

	if (Statements != NULL) {
		
		for (unsigned int i = 0; i < Statements->size(); ++i) {
			delete Statements->at(i);
		}

		delete Statements;
		Statements = NULL;

	}

	return resultAssembly;
}

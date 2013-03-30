#include "Parser.hpp"
#include <Function/ScriptedFunction.hpp>
#include <Function/FunctionReference.hpp>
#include "ParserException.hpp"
#include <string.h>

extern std::map<std::string, std::map<std::string, SP<Function>>>Namespace;
extern std::map<std::string, SmartPointer<Function>> Functions;
extern std::vector<std::string> ImportList;
extern std::vector<SmartPointer<FunctionReference>> References;
extern bool ParsingError;
extern void yyparse();
extern void yy_scan_string(char const*);
extern void yylex_destroy();

std::string Parser::bufferText(std::string const& filePath) {
	FILE* fin = fopen(filePath.c_str(), "r");

	if (fin == 0) {
		return "ERROR";
	}

	// Run to the end of the file
	fseek(fin, 0, SEEK_END);

	// Get the length of the file
	size_t f_size = ftell(fin);
	fseek(fin, 0, SEEK_SET);

	char* buffer = new char[f_size + 1];

	fread(buffer, 1, f_size, fin);
	buffer[f_size] = '\0';
	fclose(fin);

	//Create the inputSource from the buffer
	std::string inputSource = std::string(buffer);
	delete[] buffer;

	return inputSource;
}

void Parser::setupNamespace(std::string name,
		std::map<std::string, SP<Function>> functions) {
	Namespace[name] = functions;
}

SP<Function> Parser::generateProgram(std::string const& filename) {

	//Create the inputSource from the buffer
	std::string inputSource = bufferText(filename + ".scribble");

	//Clear and previous errors
	ParsingError = false;

	//Copy the input source to a buffer and then parse it ( As Bison/Flex only work with C strings)
	char* a = strdup(inputSource.c_str());

	yy_scan_string(a);
	yyparse();
	yylex_destroy();

	//Free the bison buffer
	delete[] a;

	if (ParsingError) {
		throw ParserException(filename, "Parser error occurred");
	}

	Namespace[filename] = Functions;
	Functions = std::map<std::string, SmartPointer<Function>>();

	std::vector<std::string> imports = ImportList;
	ImportList.clear();

	std::vector<SmartPointer<FunctionReference>> references = References;
	References = std::vector<SP<FunctionReference>>();

	//Look at the list of requested imports and attempt to resolve them.
	for (unsigned int i = 0; i < imports.size(); ++i) {

		//If not already loaded attempt to load the file.
		if (Namespace.find(imports[i]) == Namespace.end()) {
			generateProgram(imports[i]);
			Functions = std::map<std::string, SmartPointer<Function>>();
		}

	}

	Functions = Namespace[filename];

	//Loop through all of the references and resolve them.
	for (unsigned int i = 0; i < references.size(); ++i) {

		if (references[i]->getNamespace().size() == 0) {
			auto it = Functions.find(references[i]->getName());

			if (it != Functions.end()) {
				references[i]->setFunction(it->second);
			} else {
				printf("Could not resolve %s\n",
						references[i]->getName().c_str());
			}
		} else {
			std::map<std::string, SP<Function>> currentNamespace =
					Namespace[references[i]->getNamespace()];
			auto it = currentNamespace.find(references[i]->getName());

			if (it != currentNamespace.end()) {
				references[i]->setFunction(it->second);
			} else {
				printf("Could not resolve %s\n",
						references[i]->getName().c_str());
			}
		}

	}

	try {
		//Run the check function on all functions which will throw StatementExceptions if there is an issue.
		if (Functions.size() > 0) {

			for (auto it = Functions.begin(); it != Functions.end(); it++) {
				it->second->check();
			}

		}
	} catch (StatementException e) {
		throw ParserException(filename, e.what());
	}

	//If it hasn't return the source as a function
	return Functions["main"];
}

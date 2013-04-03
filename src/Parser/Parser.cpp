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

bool Parser::listContains(std::string target,
		std::vector<std::string> const& list) {

	for (unsigned int i = 0; i < list.size(); i++) {

		if (list[i].compare(target) == 0) {
			return true;
		}

	}

	return false;
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

			//Look for function in the current namespace
			auto it = Functions.find(references[i]->getName());

			if (it != Functions.end()) {
				references[i]->setFunction(it->second);
			} else {
				references[i]->setResolveIssue(
						references[i]->getName() + "Not defined in namespace");
			}

		} else {

			//Look for it in an external namespace

			//Check the namespace has been loaded. If not then do not resolve the reference.
			if (Parser::listContains(references[i]->getNamespace(), imports)) {

				//Pull a reference to the selected namespace.
				std::map<std::string, SP<Function>>& selectedNamespace =
						Namespace[references[i]->getNamespace()];

				//Search for function in namespace.
				auto it = selectedNamespace.find(references[i]->getName());

				//If the function is in the namespace then resolve it. otherwise leave it blank and the statement will throw an exception when checked.
				if (it != selectedNamespace.end()) {

					references[i]->setFunction(it->second);

				} else {

					references[i]->setResolveIssue(
							std::string("Function ") + references[i]->getName()
									+ " does not exist in namespace "
									+ references[i]->getNamespace());

				}

			} else {
				references[i]->setResolveIssue(
						std::string("Namespace ")
								+ references[i]->getNamespace()
								+ " has not been imported.");
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

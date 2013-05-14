#include "Parser.hpp"
#include <Function/ScriptedFunction.hpp>
#include <Function/FunctionReference.hpp>
#include <Value/Util.hpp>
#include "ParserException.hpp"
#include <string.h>

extern std::map<std::string, NamespaceType> Namespace;
extern NamespaceType Functions;

extern std::vector<std::string> ImportList;
extern std::vector<Reference> References;

extern bool ParsingError;

extern void yyparse();
extern void yy_scan_string(char const*);
extern void yylex_destroy();
extern void parser_free_all();

SP<Function> Parser::findFunctionInSet(SP<FunctionReference> toFind,
		FunctionSet const& set) {

	//If the target set is empty return null
	if (set.size() == 0) {
		return 0;
	}

	//Grab a reference to the functions arguments.
	std::vector<SafeStatement> const& args = toFind->getArgs();

	//If the function takes zero arguments then there can only be one option.
	if (args.size() == 0) {

		SP<Function> fn = set[0];

		if (fn->numArgs() == 0) {
			return fn;
		} else {
			return 0;
		}
	}

	//Otherwise search through each function and do a thorough search.
	for (unsigned int i = 0; i < set.size(); ++i) {

		SP<Function> fn = set[i];

		if (fn->numArgs() == args.size()) {

			for (unsigned int i = 0; i < args.size(); ++i) {

				SafeStatement arg = args[i];

				if (fn->argType(i) != arg->type()) {
					break;
				}

				return fn;
			}

		}

	}

	return 0;
}

std::string Parser::bufferText(std::string const& filePath) {

	FILE* fin = fopen(filePath.c_str(), "r");

	//If the file cannot be opened return an error
	if (fin == 0) {
		throw ParserException(filePath, "file could not be opened");
	}

	// Run to the end of the file
	fseek(fin, 0, SEEK_END);

	// Get the length of the file
	size_t f_size = ftell(fin);

	// Rewind to the beginning
	fseek(fin, 0, SEEK_SET);

	// Allocate space for the test
	char* buffer = new char[f_size + 1];

	// Read it in and null point the end
	fread(buffer, 1, f_size, fin);
	buffer[f_size] = '\0';

	//Close the file
	fclose(fin);

	//Create the inputSource from the buffer
	std::string inputSource = std::string(buffer);

	//Free the buffers
	delete[] buffer;

	if (f_size == 0) {
		throw ParserException(filePath, "Empty file");
	}

	return inputSource;
}

bool Parser::listContains(std::string target,
		std::vector<std::string> const& list) {

	//Check each member of the list to see if it contains the target string.
	for (unsigned int i = 0; i < list.size(); i++) {

		if (list[i].compare(target) == 0) {
			return true;
		}

	}

	return false;
}

bool Parser::functionSetAlreadyContainsEquivilent(SP<Function> function,
		FunctionSet const& functionSet) {

	bool duplicate = false;

	//For each function in a set check to see if it has the same argument types as a given function and if it does return true.

	for (unsigned int i = 0; i < functionSet.size(); ++i) {

		auto compared = functionSet[i];

		if (compared.Get() == function.Get()) {
			return true;
		} else {

			if (function->numArgs() != compared->numArgs()) {
				return false;
			}

			duplicate = true;

			for (unsigned int j = 0; j < function->numArgs(); ++j) {

				if (function->argType(j) != compared->argType(j)) {
					duplicate = false;
					break;
				}

			}

			if (duplicate) {
				return true;
			}

		}

	}

	return false;
}

unsigned int Parser::functionSetNumArguments(FunctionSet const& set) {
	SP<Function> fn = set[0];
	return fn->numArgs();
}

Type* Parser::functionSetType(FunctionSet const& functionSet) {
	SP<Function> fn = functionSet[0];
	return fn->getType();
}

NamespaceType Parser::include(std::string const& filename) {

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
	Functions = NamespaceType();

	std::vector<std::string> imports = ImportList;
	ImportList.clear();

	std::vector<Reference> references = References;
	References = std::vector<Reference>();

	//Look at the list of requested imports and attempt to resolve them.
	for (unsigned int i = 0; i < imports.size(); ++i) {

		//If not already loaded attempt to load the file.
		if (Namespace.find(imports[i]) == Namespace.end()) {
			include(imports[i]);
			Functions = NamespaceType();
		}

	}

	Functions = Namespace[filename];

	//Loop through all of the references and resolve them.
	for (unsigned int i = 0; i < references.size(); ++i) {

		if (!references[i].fRef.Null()) {

			SP<FunctionReference> ref = references[i].fRef;

			NamespaceType selectedNamespace = Functions;

			if (ref->getNamespace().size() != 0) {

				//Check the namespace has been loaded. If not then do not resolve the reference.
				if (Parser::listContains(ref->getNamespace(), imports)) {
					selectedNamespace = Namespace[ref->getNamespace()];
				} else {
					ref->setResolveIssue(
							std::string("Namespace ") + ref->getNamespace()
									+ " has not been imported.");
				}
			}

			//Search for function in namespace.
			auto it = selectedNamespace.find(ref->getName());

			//If the function is in the namespace then resolve it. otherwise leave it blank and the statement will throw an exception when checked.
			if (it == selectedNamespace.end()) {

				ref->setResolveIssue(
						std::string("the function ") + ref->getDebugName()
								+ " is not defined");

			} else {

				SP<Function> searchResult = Parser::findFunctionInSet(ref,
						it->second);

				if (!searchResult.Null()) {

					ref->setFunction(searchResult);

				} else {

					ref->setResolveIssue(
							std::string("the function ") + ref->getDebugName()
									+ " is defined but does not have any versions which take the specified argument types.");

				}

			}

		} else {

			AutoVariablePair p = references[i].avRef;

			p.first->setValue(ValueUtil::generateValue(p.second->type()));

		}

	}

	try {
		//Run the check function on all functions which will throw StatementExceptions if there is an issue.
		if (Functions.size() > 0) {

			for (auto it = Functions.begin(); it != Functions.end(); it++) {

				for (unsigned int i = 0; i < it->second.size(); ++i) {
					it->second[i]->check();
				}

			}

		}
	} catch (StatementException& e) {
		throw ParserException(filename, e.what());
	}

	return Functions;
}

NamespaceType Parser::compile(std::string const& file,
		std::map<std::string, NamespaceType> builtinNamespace) {
	parser_free_all();

	Namespace = builtinNamespace;
	NamespaceType ns = include(file);

	parser_free_all();

	return ns;
}

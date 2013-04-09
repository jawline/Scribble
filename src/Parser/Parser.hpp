#ifndef _PARSER_DEF_H_
#define _PARSER_DEF_H_
#include <Pointers/SmartPointer.hpp>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <map>
#include <Statement/Statement.hpp>
#include <Function/Function.hpp>
#include <Function/FunctionReference.hpp>

typedef std::vector<SP<Function>> FunctionSet;
typedef std::map<std::string, FunctionSet> NamespaceType;

/**
 * Parser facade, hides the Parser implementation and provides function to convert between files and returns low level code.
 */

class Parser {
private:
	static std::string bufferText(std::string const& filePath);

public:

	static void setupNamespace(std::string name,
			NamespaceType const& functions);

	//Check the number of arguments a function must have in this set
	static unsigned int functionSetNumArguments(FunctionSet const& functionSet);

	//Check whether the set already contains an equivalent function
	static bool functionSetAlreadyContainsEquivilent(SP<Function> function,
			FunctionSet const& functionSet);

	static SP<Function> findFunctionInSet(SP<FunctionReference> toFind, FunctionSet const& set);

	static SP<Function> functionSetSearch(FunctionSet const& functionSet,
			std::vector<int> argumentTypes);

	//Get the return type of a function set
	static ValueType functionSetType(FunctionSet const& functionSet);

	static bool listContains(std::string target,
			std::vector<std::string> const& list);

	static SP<Function> generateProgram(std::string const& inputSource);
};

#endif //_PARSER_DEF_H_

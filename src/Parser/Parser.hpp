#ifndef _PARSER_DEF_H_
#define _PARSER_DEF_H_

#include <Pointers/SmartPointer.hpp>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <map>
#include <Statement/Statement.hpp>
#include <Function/Function.hpp> // Function class
#include <Function/FunctionReference.hpp> // Function ref class
#include <Value/Variable.hpp> // Variable class
typedef std::vector<SP<Function>> FunctionSet;
typedef std::map<std::string, FunctionSet> NamespaceType;
typedef std::pair<SP<Variable>, SafeStatement> AutoVariablePair;

struct Reference {
	SmartPointer<FunctionReference> fRef;
	AutoVariablePair avRef;
};

/**
 * Parser facade, hides the Parser implementation and provides function to convert between files and returns low level code.
 */

class Parser {
private:
	static std::string bufferText(std::string const& filePath);

	static NamespaceType include(std::string const& inputSource);

public:

	/**
	 * Check the number of arguments a function must have in this set
	 */
	static unsigned int functionSetNumArguments(FunctionSet const& functionSet);

	/**
	 * Check whether the set already contains an equivalent function
	 */

	static bool functionSetAlreadyContainsEquivilent(SP<Function> function,
			FunctionSet const& functionSet);

	/**
	 * Attempt to find a function that meets the criteria of a reference within a function set.
	 */
	static SP<Function> findFunctionInSet(SP<FunctionReference> toFind,
			FunctionSet const& set);

	/**
	 *
	 */
	static SP<Function> functionSetSearch(FunctionSet const& functionSet,
			std::vector<int> argumentTypes);

	/**
	 * Get the return type of a function set
	 */
	static Type* functionSetType(FunctionSet const& functionSet);

	static bool listContains(std::string target,
			std::vector<std::string> const& list);

	/**
	 * Static function which will return the resulting namespace of the parsing of a given file.
	 */

	static NamespaceType compile(std::string const& file,
			std::map<std::string, NamespaceType> builtinNamespace);
};

#endif //_PARSER_DEF_H_

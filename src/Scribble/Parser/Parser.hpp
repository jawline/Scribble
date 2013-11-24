#ifndef _PARSER_DEF_H_
#define _PARSER_DEF_H_
#include "NamespaceEntry.hpp"
#include <Pointers/SmartPointer.hpp>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <map>
#include <Scribble/Statement/Statement.hpp>
#include <API/Function.hpp> // Function class
#include <Scribble/Function/FunctionReference.hpp> // Function ref class
#include <Scribble/Statement/GetStructureElementStatement.hpp>
#include <Scribble/Statement/StructureAssignElement.hpp>
#include <Scribble/Value/Variable.hpp> // Variable class

typedef std::vector<SP<Function>> FunctionSet;
typedef std::map<std::string, NamespaceEntry> NamespaceType;
typedef std::pair<SP<Variable>, SafeStatement> AutoVariablePair;

enum ParserReferenceType {
	FunctionEvaluation,
	StructureElementTypeEvaluation,
	AssignElementTypeEvaluation,
	VariableTypeEvaluation
};

class ParserReference {
private:
	ParserReferenceType type_;

public:

	ParserReference(SP<FunctionReference> reference) {
		type_ = FunctionEvaluation;
		functionReference = reference;
	}

	ParserReference(GetStructureElementStatement* elementType) {
		type_ = StructureElementTypeEvaluation;
		structureElementType = elementType;
	}

	ParserReference(StructureAssignElement* assign) {
		type_ = AssignElementTypeEvaluation;
		assignElementType = assign;
	}

	ParserReference(AutoVariablePair pair) {
		type_ = VariableTypeEvaluation;
		autoVariableType = pair;
	}

	ParserReferenceType type() {
		return type_;
	}

	SmartPointer<FunctionReference> functionReference;
	GetStructureElementStatement* structureElementType;
	StructureAssignElement* assignElementType;
	AutoVariablePair autoVariableType;
};


const static std::string ScribbleFileSuffix = ".sc";

/**
 * Parser facade, hides the Parser implementation and provides function to convert between files and returns low level code.
 */

class Parser {
private:
	static std::string bufferText(std::string const& filePath);

	static std::string include(std::string const& inputSource,
			std::string const& path);

	static std::string includeText(std::string source, std::string const& filename, std::string const& path);

	static void printNamespace(NamespaceType const& ns);
	static void printAllSpaces(std::map<std::string, NamespaceType> const& ns);
	static void resolve(TypeReference reference, NamespaceType ns);
	static std::string getUniformPath(std::string const& path);

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

	static std::map<std::string, NamespaceType> compile(std::string const& file,
			std::map<std::string, NamespaceType> builtinNamespace);

	static std::map<std::string, NamespaceType> compileText(std::string const& text, std::string const& packageName,
			std::map<std::string, NamespaceType> builtinNamespace);

};

#endif //_PARSER_DEF_H_

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
#include "ParserReference.hpp"

namespace ScribbleCore {

typedef std::vector<SafeFunction> FunctionSet;
typedef std::map<std::string, NamespaceEntry> NamespaceType;

const static std::string ScribbleFileSuffix = ".sc";

/**
 * Code parser & compiler, parses source text into a program which can be executed
 */
class Parser {
  private:

    /**
     * Buffer the given file and return it's contents as a std::string.
     */
    static std::string bufferText(std::string const& filePath);

    /**
     * Include the specified file, resolving it from the path.
     */
    static std::string include(std::string const& inputFile,
                               std::string const& path);

    /**
     * Include the given source text as the specified filename.
     */
    static std::string includeText(std::string source,
                                   std::string const& filename, std::string const& path);

    static void printFunctionSet(std::string name, FunctionSet fs);
    static void printNamespace(NamespaceType const& ns);
    static void printAllSpaces(std::map<std::string, NamespaceType> const& ns);
    static void resolve(TypeReference reference, NamespaceType ns);
    static void resetImportList();
    static void resetReferences();
    static void resetFunctions();

  public:

    /**
     * Check whether the set already contains an equivalent function
     */
    static bool signatureEquals(SafeFunction function, SafeFunction other);

    /**
     * Attempt to find a function that meets the criteria of a reference within a function set.
     */
    static SafeFunction findFunctionInSet(SmartPointer<FunctionReference> toFind,
            FunctionSet const& set);

    /**
     * Search a list of strings and return true if it contains the target string
     */
    static bool listContains(std::string target,
                             std::vector<std::string> const& list);

    /**
     * Static function which will return the resulting namespace of the parsing of a given file.
     */
    static std::map<std::string, NamespaceType> compile(std::string const& file,
            std::map<std::string, NamespaceType> builtinNamespace);

    /**
     * Static function which will create a namespace from a piece of source text given as a string
     */
    static std::map<std::string, NamespaceType> compileText(std::string const&text, std::string const& packageName,
            std::map<std::string, NamespaceType> builtinNamespace);

    /**
     * Return an internal uniform path of a given file ( For example ../src/Test and Test would return the same string ) if the file exists
     * or return input string if the file does not exist.
     */
    static std::string getUniformPath(std::string const& path);
};

}

#endif //_PARSER_DEF_H_

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

/**
 * Parser facade, hides the Parser implementation and provides function to convert between files and returns low level code.
 */

class Parser {
private:
	static std::string bufferText(std::string const& filePath);

public:

	static void setupNamespace(std::string name,
			std::map<std::string, SP<Function>> functions);

	static SP<Function> generateProgram(std::string const& inputSource);
};

#endif //_PARSER_DEF_H_

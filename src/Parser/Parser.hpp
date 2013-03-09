#ifndef _PARSER_DEF_H_
#define _PARSER_DEF_H_
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
public:
	static Function* generateProgram(std::string inputSource);
};

#endif //_PARSER_DEF_H_

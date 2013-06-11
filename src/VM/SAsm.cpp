/*
 * SAsm.cpp
 *
 *  Created on: 11 Jun 2013
 *      Author: blake
 */

#include "SAsm.hpp"
#include <stdint.h>
#include <string>
#include <algorithm>    // std::find_if


namespace SimpleASM {

// trim from start
static inline std::string &ltrim(std::string &s) {
	s.erase(s.begin(),
			std::find_if(s.begin(), s.end(),
					std::not1(std::ptr_fun<int, int>(std::isspace))));
	return s;
}

// trim from end
static inline std::string &rtrim(std::string &s) {
	s.erase(
			std::find_if(s.rbegin(), s.rend(),
					std::not1(std::ptr_fun<int, int>(std::isspace))).base(),
			s.end());
	return s;
}

// trim from both ends
static inline std::string &trim(std::string &s) {
	return ltrim(rtrim(s));
}

SAsm::SAsm() {
	// TODO Auto-generated constructor stub

}

SAsm::~SAsm() {
	// TODO Auto-generated destructor stub
}

void NextLine(std::string& toRead, std::string& current) {

	size_t endline = toRead.find("\n");

	if (endline == std::string::npos) {
		current = toRead;
		toRead = "";
	} else {
		current = toRead.substr(0, endline);
		toRead = toRead.substr(endline, toRead.length());
	}

}

VM::InstructionSet SAsm::parse(std::string text) {

	std::string toRead = text;
	std::string current = "";

	uint8_t* buffer = new uint8_t[5000];
	int currentInst;

	NextLine(toRead, current);

	while (toRead.length() > 0) {
		current = trim(current);
		printf("Line %s\n", current.c_str());
		NextLine(toRead, current);
	}

	return VM::InstructionSet(buffer, currentInst, 0);
}

} /* namespace SimpleASM */

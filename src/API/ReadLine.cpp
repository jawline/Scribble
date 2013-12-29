/*
 * ReadLine.cpp
 *
 *  Created on: 5 Jun 2013
 *      Author: blake
 */

#include "ReadLine.hpp"

ReadLine::ReadLine(std::string ns) :
		Function("ReadLine", ns) {
	// TODO Auto-generated constructor stub

}

ReadLine::~ReadLine() {
	// TODO Auto-generated destructor stub
}

APIValue ReadLine::execute(API::APIValue* values, VM::VirtualMachine* virt) {
	std::string line;
	std::getline(std::cin, line);

	return API::APIValue::makeString(line, virt);
}

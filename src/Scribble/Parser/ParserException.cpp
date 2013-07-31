/*
 * ParserException.cpp
 *
 *  Created on: 28 Mar 2013
 *      Author: blake
 */

#include "ParserException.hpp"

ParserException::ParserException(std::string file, std::string details) : file_(file), details_(details) {
	error_ = std::string("Parser Exception in file ") + file_ + " " + details_;
}

ParserException::~ParserException() throw() {
}

const char* ParserException::what() const throw() {
	return error_.c_str();
}

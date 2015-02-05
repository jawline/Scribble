/*
 * Util.cpp
 *
 *  Created on: 19 Mar 2013
 *      Author: blake
 */

#include "Util.hpp"
#include <sstream>
#include <exception>

UtilException::UtilException(std::string const& reason) throw () :
    reason_(reason) {}

UtilException::~UtilException() throw () {}

const char* UtilException::what() const throw () {
    return reason_.c_str();
}

/*
 * Util.cpp
 *
 *  Created on: 19 Mar 2013
 *      Author: blake
 */

#include "Util.hpp"
#include "Int.hpp"
#include "String.hpp"
#include "Void.hpp"
#include "Bool.hpp"
#include <exception>

UtilException::UtilException(std::string const& reason) throw () :
		reason_(reason) {

}

UtilException::~UtilException() throw () {

}

const char* UtilException::what() const throw () {
	return reason_.c_str();
}

ValueUtil::ValueUtil() {
	// TODO Auto-generated constructor stub

}

ValueUtil::~ValueUtil() {
	// TODO Auto-generated destructor stub
}

Value* ValueUtil::generateValue(Type* type) {

	switch (type->getType()) {

	case Int:
		return new IntValue(0);
		break;

	case String:
		return new StringValue("");
		break;

	case Void:
		return new VoidValue();
		break;

	case Boolean:
		return new BoolValue(false);

	default:
		break;
	}

	throw UtilException("Type generation not valid/unimplemented");
}

bool ValueUtil::sameType(Value* a, Value* b) {

	if (a->type() != b->type()) {
		return false;
	}

	return true;
}

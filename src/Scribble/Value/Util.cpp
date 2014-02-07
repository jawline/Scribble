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
#include "Array.hpp"
#include "Structure.hpp"
#include "Float32.hpp"
#include <sstream>
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

	case Array:
		return new ArrayValue(type);

	case Int:
		return new IntValue(0);

	case Float32:
		return new Float32Value(0);

	case Void:
		return new VoidValue();

	case Boolean:
		return new BoolValue(false);

	case StructureType:
		return new Structure(type);

	default:
		break;
	}

	std::stringstream s;
	s << "Type ";
	s << type->getType();
	s << " generation not valid/implemented";
	throw UtilException(s.str());
}

bool ValueUtil::sameType(Value* a, Value* b) {

	if (a->type() != b->type()) {
		return false;
	}

	return true;
}

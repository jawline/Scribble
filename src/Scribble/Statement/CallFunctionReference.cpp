/*
 * CallFunctionReference.cpp
 *
 *  Created on: 5 Jun 2014
 *      Author: blake
 */

#include "CallFunctionReference.hpp"

namespace ScribbleCore {

CallFunctionReference::CallFunctionReference(int lineNo, std::string sym,
		SafeStatement fn, std::vector<SafeStatement> args) :
		Statement(lineNo, sym) {

}

CallFunctionReference::~CallFunctionReference() {
}

} /* namespace ScribbleCore */

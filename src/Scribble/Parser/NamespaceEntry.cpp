/*
 * NamespaceEntry.cpp
 *
 *  Created on: 25 May 2013
 *      Author: blake
 */

#include "NamespaceEntry.hpp"

namespace ScribbleCore {

NamespaceEntry::NamespaceEntry() {
	type_ = EmptyEntry;
}

NamespaceEntry::NamespaceEntry(TypeReference t) {
	type_ = TypeEntry;
	typeInfo_ = t;
}

NamespaceEntry::NamespaceEntry(std::vector<SafeFunction> set) {
	type_ = FunctionSetEntry;
	functionSet_ = set;
}

NamespaceEntry::~NamespaceEntry() {
}

EntryType NamespaceEntry::type() {
	return type_;
}

std::vector<SafeFunction> NamespaceEntry::getFunctionSet() {
	return functionSet_;
}

TypeReference NamespaceEntry::getType() {
	return typeInfo_;
}

void NamespaceEntry::addFunctionToSet(SafeFunction f) {
	functionSet_.push_back(f);
}

}

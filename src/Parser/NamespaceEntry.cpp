/*
 * NamespaceEntry.cpp
 *
 *  Created on: 25 May 2013
 *      Author: blake
 */

#include "NamespaceEntry.hpp"

NamespaceEntry::NamespaceEntry() {
	type_ = EmptyEntry;
}

NamespaceEntry::NamespaceEntry(Type* t) {
	type_ = TypeEntry;
	typeInfo_ = t;
}

NamespaceEntry::NamespaceEntry(std::vector<SafeFunction> set) {
	type_ = FunctionSetEntry;
	functionSet_ = set;
}

NamespaceEntry::~NamespaceEntry() {
	// TODO Auto-generated destructor stub
}

EntryType NamespaceEntry::type() {
	return type_;
}

std::vector<SafeFunction> NamespaceEntry::getFunctionSet() {
	return functionSet_;
}

Type* NamespaceEntry::getType() {
	return typeInfo_;
}

void NamespaceEntry::addFunctionToSet(SafeFunction f) {
	functionSet_.push_back(f);
}

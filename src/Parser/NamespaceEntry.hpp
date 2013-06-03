/*
 * NamespaceEntry.hpp
 *
 *  Created on: 25 May 2013
 *      Author: blake
 */

#ifndef NAMESPACEENTRY_HPP_
#define NAMESPACEENTRY_HPP_
#include <Function/Function.hpp>
#include <Parser/TypeReference.hpp>

enum EntryType {
	EmptyEntry,
	FunctionSetEntry,
	TypeEntry
};

class NamespaceEntry {
private:
	EntryType type_;
	TypeReference typeInfo_;
	std::vector<SafeFunction> functionSet_;

public:
	NamespaceEntry();
	NamespaceEntry(TypeReference t);
	NamespaceEntry(std::vector<SafeFunction> set);
	virtual ~NamespaceEntry();

	EntryType type();
	std::vector<SafeFunction> getFunctionSet();
	void addFunctionToSet(SafeFunction f);
	TypeReference getType();
};

#endif /* NAMESPACEENTRY_HPP_ */

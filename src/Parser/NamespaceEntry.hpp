/*
 * NamespaceEntry.hpp
 *
 *  Created on: 25 May 2013
 *      Author: blake
 */

#ifndef NAMESPACEENTRY_HPP_
#define NAMESPACEENTRY_HPP_
#include <Function/Function.hpp>
#include <Value/Type.hpp>

enum EntryType {
	EmptyEntry,
	FunctionSetEntry,
	TypeEntry
};

class NamespaceEntry {
private:
	EntryType type_;
	Type* typeInfo_;
	std::vector<SafeFunction> functionSet_;

public:
	NamespaceEntry();
	NamespaceEntry(Type* t);
	NamespaceEntry(std::vector<SafeFunction> set);
	virtual ~NamespaceEntry();

	EntryType type();
	std::vector<SafeFunction> getFunctionSet();
	void addFunctionToSet(SafeFunction f);
	Type* getType();
};

#endif /* NAMESPACEENTRY_HPP_ */

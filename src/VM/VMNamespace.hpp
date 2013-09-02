/*
 * VMNamespace.hpp
 *
 *  Created on: 31 Aug 2013
 *      Author: blake
 */

#ifndef VMNAMESPACE_HPP_
#define VMNAMESPACE_HPP_
#include <string>
#include <string>
#include <map>
#include "VMFunc.hpp"
#include "VMEntryType.hpp"

namespace VM {

enum NamespaceEntryType {
	Invalid, Function, Type, Namespace
};

class NamespaceEntry;

typedef std::map<std::string, NamespaceEntry> VMNamespace;

class NamespaceEntry {
private:

	NamespaceEntryType type_;
	VMFunc funcRef_;SP<VMEntryType> typeRef_;
	VMNamespace namespace_;

public:

	NamespaceEntry() {
		type_ = Invalid;
	}

	NamespaceEntry(VMNamespace names) {
		type_ = Namespace;
		namespace_ = names;
	}

	NamespaceEntry(VMFunc func) {
		type_ = Function;
		funcRef_ = func;
	}

	NamespaceEntry(SP<VMEntryType> type) {
		type_ = Type;
		typeRef_ = type;
	}

	VMNamespace getNamespace() {
		return namespace_;
	}

	SP<VMEntryType> getTypeReference() {
		return typeRef_;
	}

	VMFunc getFunction() {
		return funcRef_;
	}

	NamespaceEntryType getType() {
		return type_;
	}

};

bool searchNamespace(VM::VMNamespace space, std::string target, NamespaceEntry& entry);

}

#endif /* VMNAMESPACE_HPP_ */

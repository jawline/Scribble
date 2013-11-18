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
#include <Util/HashMap.hpp>
#include "VMFunc.hpp"
#include "VMEntryType.hpp"

namespace VM {

enum NamespaceEntryType {
	Invalid, Function, Type, Namespace
};

class NamespaceEntry;

typedef HashMap<NamespaceEntry> VMNamespace;

class NamespaceEntry {
private:

	NamespaceEntryType type_;
	SmartPointer<VMFunc> funcRef_;
	SmartPointer<VMEntryType> typeRef_;
	VMNamespace namespace_;

public:

	NamespaceEntry() {
		type_ = Invalid;
	}

	NamespaceEntry(VMNamespace names) {
		type_ = Namespace;
		namespace_ = names;
	}

	NamespaceEntry(SP<VMFunc> func) {
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

	SP<VMFunc> getFunction() {
		return funcRef_;
	}

	NamespaceEntryType getType() {
		return type_;
	}

};

bool searchNamespace(VM::VMNamespace space, std::string target,
		NamespaceEntry& entry);

}

#endif /* VMNAMESPACE_HPP_ */

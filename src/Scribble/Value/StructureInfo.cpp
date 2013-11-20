/*
 * StructureInfo.cpp
 *
 *  Created on: 25 May 2013
 *      Author: blake
 */

#include "StructureInfo.hpp"
#include <VM/Constants.hpp>

StructureInfo::StructureInfo(std::string name) :
		Type(StructureType, nullptr), name_(name), namespace_("__INVALID__NAMESPACE__") {
}

StructureInfo::~StructureInfo() {
}

void StructureInfo::addInfo(std::string name, TypeReference t) {
	dataIndexs_.push_back(std::pair<std::string, TypeReference>(name, t));
}

unsigned int StructureInfo::getNumIndexs() {
	return dataIndexs_.size();
}

int StructureInfo::getIndex(std::string name) {

	for (unsigned int i = 0; i < dataIndexs_.size(); ++i) {

		if (dataIndexs_[i].first == name) {
			return i;
		}

	}

	return -1;
}

Type* StructureInfo::getType(std::string name) {

	if (getIndex(name) != -1) {
		return dataIndexs_[getIndex(name)].second->type;
	}

	return nullptr;
}

std::pair<std::string, TypeReference> StructureInfo::getIndex(int index) {
	return dataIndexs_[index];
}

void StructureInfo::setName(std::string name) {
	name_ = name;
}

void StructureInfo::setNamespace(std::string name) {
	namespace_ = name;
}

std::string StructureInfo::getTypeName() {
	return getNamespace() + VM::vmNamespaceSeperator + getName();
}

std::string StructureInfo::getNamespace() {
	return namespace_;
}

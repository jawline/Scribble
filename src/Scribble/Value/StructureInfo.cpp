/*
 * StructureInfo.cpp
 *
 *  Created on: 25 May 2013
 *      Author: blake
 */

#include "StructureInfo.hpp"

StructureInfo::StructureInfo() :
		Type(StructureType, nullptr) {
}

StructureInfo::~StructureInfo() {
}

void StructureInfo::addInfo(std::string name, TypeReference t) {
	dataIndexs_.push_back(std::pair<std::string, TypeReference>(name, t));
}

int StructureInfo::getNumIndexs() {
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

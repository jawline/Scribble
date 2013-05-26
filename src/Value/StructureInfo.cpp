/*
 * StructureInfo.cpp
 *
 *  Created on: 25 May 2013
 *      Author: blake
 */

#include "StructureInfo.hpp"

StructureInfo::StructureInfo() : Type(StructureInfoType, nullptr) {
}

StructureInfo::~StructureInfo() {
}

void StructureInfo::addInfo(std::string name, Type* t) {
	dataIndexs_[name] = t;
}

int StructureInfo::getNumIndexs() {
	return dataIndexs_.size();
}

Type* StructureInfo::getType(std::string name) {
	return dataIndexs_[name];
}

std::pair<std::string, Type*> StructureInfo::getIndex(int index) {

	auto iter = dataIndexs_.begin();

	for (int i = 0; i < index; ++i) {
		iter++;
	}

	return std::pair<std::string, Type*>(iter->first, iter->second);
}

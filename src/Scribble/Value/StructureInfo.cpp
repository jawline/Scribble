/*
 * StructureInfo.cpp
 *
 *  Created on: 25 May 2013
 *      Author: blake
 */

#include "StructureInfo.hpp"
#include <VM/Constants.hpp>

namespace ScribbleCore {

StructureInfo::StructureInfo(std::string name) :
    Type(StructureType, nullptr), name_(name), package_(
        "__INVALID__NAMESPACE__") {}

StructureInfo::~StructureInfo() {}

void StructureInfo::addInfo(std::string name, TypeReference t) {
    dataIndexs_.push_back(std::pair<std::string, TypeReference>(name, t));
}

unsigned int StructureInfo::getNumFields() const {
    return dataIndexs_.size();
}

int StructureInfo::getFieldIndex(std::string const& name) const {

    for (unsigned int i = 0; i < dataIndexs_.size(); ++i) {
        if (dataIndexs_[i].first == name) {
            return i;
        }
    }

    return -1;
}

bool StructureInfo::Equals(Type* other) const {
    return other == this;
}

Type* StructureInfo::getFieldType(std::string const& name) const {

    if ((int index = getFieldIndex(name)) != -1) {
        return dataIndexs_[index].second->type();
    }

    return nullptr;
}

std::pair<std::string, TypeReference> StructureInfo::getField(int index) const {
    return dataIndexs_[index];
}

void StructureInfo::setName(std::string const& name) {
    name_ = name;
}

void StructureInfo::setPackage(std::string const& name) {
    package_ = name;
}

std::string StructureInfo::getTypeName() const {
    return getPackage() + VM::vmNamespaceSeperator + getName();
}

std::string StructureInfo::getPackage() const {
    return package_;
}

std::string StructureInfo::getName() const {
    return name_;
}

}

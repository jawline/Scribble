/*
 * StructureInfo.hpp
 *
 *  Created on: 25 May 2013
 *      Author: blake
 */

#ifndef STRUCTUREINFO_HPP_
#define STRUCTUREINFO_HPP_
#include <string>
#include <vector>
#include <Scribble/Parser/TypeReference.hpp>
#include "Type.hpp"

class StructureInfo : public Type {
private:
	std::string name_;
	std::vector<std::pair<std::string, TypeReference>> dataIndexs_;

public:
	StructureInfo(std::string name);
	virtual ~StructureInfo();

	void addInfo(std::string name, TypeReference type);
	std::pair<std::string, TypeReference> getIndex(int i);
	Type* getType(std::string name);
	int getIndex(std::string name);
	int getNumIndexs();

	StructureInfo setName(std::string name) {
		name_ = name;
		return *this;
	}

	virtual std::string getTypeName() {
		return "struct#" + name_;
	}
};

typedef StructureInfo SInfo;

#endif /* STRUCTUREINFO_HPP_ */

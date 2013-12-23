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

class StructureInfo: public Type {
private:
	std::string name_;
	std::string namespace_;

	std::vector<std::pair<std::string, TypeReference>> dataIndexs_;

public:
	StructureInfo(std::string name);
	virtual ~StructureInfo();

	void addInfo(std::string name, TypeReference type);
	std::pair<std::string, TypeReference> getIndex(int i);
	Type* getType(std::string name);
	int getIndex(std::string name);
	unsigned int getNumIndexs();

	void setName(std::string name);
	void setNamespace(std::string name);

	std::string getName() {
		return "__struct(" + name_ + ")";
	}

	/**
	 * Overrides Type::getTypeName() to return more complex structure name.
	 */

	virtual std::string getTypeName();

	std::string getNamespace();

};

typedef StructureInfo SInfo;

#endif /* STRUCTUREINFO_HPP_ */

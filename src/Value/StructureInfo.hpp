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
#include <Parser/TypeReference.hpp>
#include "Type.hpp"

class StructureInfo : public Type {
private:
	std::vector<std::pair<std::string, TypeReference>> dataIndexs_;

public:
	StructureInfo();
	virtual ~StructureInfo();

	void addInfo(std::string name, TypeReference type);
	std::pair<std::string, TypeReference> getIndex(int i);
	Type* getType(std::string name);
	int getIndex(std::string name);
	int getNumIndexs();
};

typedef StructureInfo SInfo;

#endif /* STRUCTUREINFO_HPP_ */

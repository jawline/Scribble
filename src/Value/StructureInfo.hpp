/*
 * StructureInfo.hpp
 *
 *  Created on: 25 May 2013
 *      Author: blake
 */

#ifndef STRUCTUREINFO_HPP_
#define STRUCTUREINFO_HPP_
#include <string>
#include <map>
#include "Type.hpp"

class StructureInfo : public Type {
private:
	std::map<std::string, Type*> dataIndexs_;

public:
	StructureInfo();
	virtual ~StructureInfo();

	void addInfo(std::string name, Type* type);
	std::pair<std::string, Type*> getIndex(int i);
	Type* getType(std::string name);
	int getNumIndexs();
};

#endif /* STRUCTUREINFO_HPP_ */

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

/**
 * StructureInfo contains the fields ( Name and type )  within a structure, its name and namespace.
 * The order in which fields are defined
 */

class StructureInfo: public Type {
private:

	/**
	 * The name of the structure.
	 */

	std::string name_;

	/**
	 * The name of the package it is in
	 */

	std::string package_;

	std::vector<std::pair<std::string, TypeReference>> dataIndexs_;

public:
	StructureInfo(std::string name);
	virtual ~StructureInfo();

	void addInfo(std::string name, TypeReference type);
	std::pair<std::string, TypeReference> getIndex(int i);
	Type* getType(std::string const& name);
	int getIndex(std::string const& name);
	unsigned int getNumIndexs();

	void setName(std::string const& name);
	void setPackage(std::string const& name);

	std::string getName() {
		return "__struct(" + name_ + ")";
	}

	/**
	 * Overrides Type::getTypeName() to return more complex structure name.
	 */

	virtual std::string getTypeName();

	std::string getPackage();

};

typedef StructureInfo SInfo;

#endif /* STRUCTUREINFO_HPP_ */

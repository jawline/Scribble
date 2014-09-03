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

namespace ScribbleCore {

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
	int getFieldIndex(std::string const& name);
	unsigned int getNumIndexs();

	/**
	 * Set the stored name of the structure
	 */

	void setName(std::string const& name);

	/**
	 * Change the stored name of the structures package
	 * (NOTE: To do this moving it in any namespaces will be required.
	 * setPackage will not immediately make this structure belong to
	 * another package)
	 */

	void setPackage(std::string const& name);

	/**
	 * Returns true if this type is another type
	 */

	bool Equals(Type* other) const;

	/**
	 * Return the name of this package
	 */

	std::string getName() const;

	/**
	 * Return the name of the package in which this structure resides
	 */

	std::string getPackage() const;

	/**
	 * Overrides Type::getTypeName() to return more complex structure name.
	 */

	virtual std::string getTypeName() const;

};

typedef StructureInfo SInfo;

}

#endif /* STRUCTUREINFO_HPP_ */

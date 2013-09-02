/*
 * VMNamespace.cpp
 *
 *  Created on: 31 Aug 2013
 *      Author: blake
 */

#include "VMNamespace.hpp"

bool VM::searchNamespace(VMNamespace space, std::string target, NamespaceEntry& entry) {

	size_t pos = target.find(".");

	if (pos == std::string::npos) {

		auto spaceSearch = space.find(target);
		if (spaceSearch == space.end()) {
			printf("Could not find %s\n", target.c_str());
			return false;
		}

		entry = spaceSearch->second;
		return true;
	} else {

		std::string nextSpace = target.substr(0, pos);
		std::string spaceAfter = target.substr(pos+1);

		if (space[nextSpace].getType() != Namespace) {
			printf("Could not find %s\n", nextSpace.c_str());
			return false;
		}

		return searchNamespace(space[nextSpace].getNamespace(), spaceAfter, entry);
	}

}

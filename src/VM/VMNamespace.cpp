/*
 * VMNamespace.cpp
 *
 *  Created on: 31 Aug 2013
 *      Author: blake
 */

#include "VMNamespace.hpp"
#include <VM/Constants.hpp>

bool VM::searchNamespace(VMNamespace space, std::string target, NamespaceEntry& entry) {

	size_t pos = target.find(VM::vmNamespaceSeperator);

	if (pos == std::string::npos) {

		auto spaceSearch = space.find(target);
		if (spaceSearch == space.end()) {
			//printf("Could not find %s\n", target.c_str());
			return false;
		}

		entry = spaceSearch->second;
		return true;
	} else {

		std::string prefix = target.substr(0, pos);
		target = target.substr(pos+1);

		if (space[prefix].getType() != Namespace) {
			//printf("Could not find %s\n", nextSpace.c_str());
			return false;
		}

		return searchNamespace(space[prefix].getNamespace(), target, entry);
	}

}

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

		NamespaceEntry spaceSearch = space.find(target);
		if (spaceSearch.getType() == Invalid) {
			//printf("Could not find %s\n", target.c_str());
			return false;
		}

		entry = spaceSearch;
		return true;
	} else {

		std::string prefix = target.substr(0, pos);
		target = target.substr(pos+1);

		if (space.find(prefix).getType() != Namespace) {
			//printf("Could not find %s\n", nextSpace.c_str());
			return false;
		}

		return searchNamespace(space.find(prefix).getNamespace(), target, entry);
	}

}

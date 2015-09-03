/*
 * VMNamespace.cpp
 *
 *  Created on: 31 Aug 2013
 *      Author: blake
 */

#include "VMNamespace.hpp"
#include <VM/Constants.hpp>

bool VM::NamespaceEntry::searchNamespace(VMNamespace space, std::string target, NamespaceEntry& result) {

    size_t pos = target.find(VM::vmNamespaceSeperator);

    if (pos == std::string::npos) {

        NamespaceEntry spaceSearch;
        bool found = space.get(target, spaceSearch);

        if (!found || spaceSearch.getType() == Invalid) {
            return false;
        }

        result = spaceSearch;
        return true;
    } else {

        std::string prefix = target.substr(0, pos);
        target = target.substr(pos + 1);
        NamespaceEntry localEntry;
        bool found = space.get(prefix, localEntry);

        if (!found || localEntry.getType() != Namespace) {
            return false;
        }

        return searchNamespace(localEntry.getNamespace(), target, result);
    }

}
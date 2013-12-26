/*
 * RegisterPackages.hpp
 *
 *  Created on: 26 Dec 2013
 *      Author: blake
 */

#ifndef REGISTERPACKAGES_HPP_
#define REGISTERPACKAGES_HPP_
#include <Scribble/Parser/Parser.hpp>
#include <VM/VirtualMachine.hpp>
#include <VM/VMNamespace.hpp>

void registerPackages(std::map<std::string, NamespaceType>& allNames,
		VM::VirtualMachine& vm);

#endif /* REGISTERPACKAGES_HPP_ */

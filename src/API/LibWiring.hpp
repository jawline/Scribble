/*
 * LibWiring.hpp
 *
 *  Created on: 29 Dec 2014
 *      Author: blake
 */

#ifndef LIBWIRING_HPP_
#define LIBWIRING_HPP_
#include "APIFunction.hpp"
#include <Scribble/Value/TypeManager.hpp>
#include <Scribble/Parser/Parser.hpp>
#include <API/Value/APIValue.hpp>
#include <VM/VirtualMachine.hpp>
#include <VM/VMNamespace.hpp>

void generateLibWiringPackage(
    std::map<std::string, ScribbleCore::NamespaceType>& all);

#endif /* LIBWIRING_HPP_ */
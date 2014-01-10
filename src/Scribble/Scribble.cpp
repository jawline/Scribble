/*
 * Scribble.cpp
 *
 *  Created on: 27 Dec 2013
 *      Author: blake
 */

#include "Scribble.hpp"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <Scribble/Statement/Statement.hpp>
#include <Scribble/Value/StructureInfo.hpp>
#include <Scribble/Statement/Heap.hpp>
#include <Scribble/Parser/Parser.hpp>
#include <Scribble/Parser/ParserException.hpp>
#include <Scribble/Value/TypeManager.hpp>
#include <SASM/Parser.hpp>
#include <VM/OpCodes.hpp>
#include <VM/VirtualMachine.hpp>

/**
 * API/System defines the generateSystemPackage function which creates the sys library.
 */

#include <API/System.hpp>
#include <API/Console.hpp>

#include <API/RegisterPackages.hpp>

Scribble::Scribble(std::string const& package) {
	packagePath = package;
	load();
}

Scribble::~Scribble() {
}

API::APIValue Scribble::execute(std::string function) {

	auto entry = compiledPackages[Parser::getUniformPath(packagePath)].find(
			function);

	//Check that the __init__ code has compiled properly.
	if (entry == compiledPackages["__init__"].end()
			|| entry->second.type() != FunctionSetEntry
			|| entry->second.getFunctionSet().size() != 1
			|| entry->second.getFunctionSet()[0]->numArgs() != 0) {
		printf("Function %s does not exist\n", function.c_str());
		return API::APIValue(0);
	}

	//Grab a reference to __init__.__init__ for execution
	API::SafeFunction toExecute = compiledPackages[Parser::getUniformPath(
			packagePath)][function].getFunctionSet()[0];

	std::string vmFuncName = toExecute->getNamespace()
			+ VM::vmNamespaceSeperator + toExecute->getName();

	environment.execute(vmFuncName);
	environment.printState();

	API::APIValue result;

	if (!toExecute->getType()->Equals(getVoidType())) {

		long val = 0;
		bool ref = 0;

		environment.getRegister(VM::vmReturnResultRegister, val, ref);

		if (ref) {
			result = API::APIValue(environment.getHeap().getType(val),
					environment.getHeap().getAddress(val), val);
		} else {
			result = API::APIValue(val);
		}

	} else {
		result = API::APIValue(0);
	}

	return result;
}

void Scribble::load() {

	//Generate the sys package
	generateSystemPackage(compiledPackages);

	//Generate the console package
	generateConsolePackage(compiledPackages);

	//Compile the program
	compiledPackages = Parser::compile(packagePath, compiledPackages);

	//Compile the virtual machine from the packages.
	registerPackages(compiledPackages, environment);
}

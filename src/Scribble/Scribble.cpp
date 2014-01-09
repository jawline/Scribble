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
#include <cputime.hpp>

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

#include <API/RegisterPackages.hpp>

Scribble::Scribble(std::string const& package) {
	packagePath = package;
	load();
}

Scribble::~Scribble() {
}

void Scribble::execute(std::string function) {

	auto entry = compiledPackages[Parser::getUniformPath(packagePath)].find(function);

	//Check that the __init__ code has compiled properly.
	if (entry == compiledPackages["__init__"].end()
			|| entry->second.type() != FunctionSetEntry
			|| entry->second.getFunctionSet().size() != 1
			|| entry->second.getFunctionSet()[0]->numArgs()
					!= 0) {
		printf("Function %s does not exist\n", function.c_str());
		return;
	}

	//Grab a reference to __init__.__init__ for execution
	API::SafeFunction toExecute =
			compiledPackages[Parser::getUniformPath(packagePath)][function].getFunctionSet()[0];

	VM::VirtualMachine environment;

	registerPackages(compiledPackages, environment);

	vmFuncName = toExecute->getNamespace() + VM::vmNamespaceSeperator
			+ toExecute->getName();

	double vmStart = getCPUTime();

	environment.execute(vmFuncName);

	double vmEnd = getCPUTime();

	environment.printState();

	printf("VM execution took time %f\n", vmEnd - vmStart);

}

void Scribble::load() {

	//Generate the sys package
	generateSystemPackage (compiledPackages);

	//Compile the program
	compiledPackages = Parser::compile(packagePath, compiledPackages);
}

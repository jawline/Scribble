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
	packageName = strrchr(package.c_str(), '/');
	load();
}

Scribble::~Scribble() {
}

void Scribble::execute(std::string code) {

	compiledPackages.erase("__init__");

	//Write an initialization function based off the the parameters given
	std::string initCode = writeInit(packagePath, code);

	compiledPackages = Parser::compileText(initCode, "__init__", compiledPackages);

	//Check that the __init__ code has compiled properly.
	if (compiledPackages["__init__"].find("__init__") == compiledPackages["__init__"].end()
			|| compiledPackages["__init__"]["__init__"].type() != FunctionSetEntry
			|| compiledPackages["__init__"]["__init__"].getFunctionSet().size() != 1
			|| compiledPackages["__init__"]["__init__"].getFunctionSet()[0]->numArgs()
					!= 0) {
		printf("Init function did not create properly\n");
		return;
	}

	//Grab a reference to __init__.__init__ for execution
	API::SafeFunction toExecute =
			compiledPackages["__init__"]["__init__"].getFunctionSet()[0];

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

std::string Scribble::writeInit(std::string const& package,
		std::string const& execStr) {

	if (package.size() == 0) {

		std::string result = "package sys := import(\"sys\");\n";

		result += "func __init__() {\n";
		result += execStr;
		result += "}\n";

		return result;
	} else {

		std::string result =
				"package sys := import(\"sys\");\npackage target := import(\""
						+ package + "\");\n";

		result += "func __init__() {\n";
		result += execStr;
		result += "}\n";

		return result;
	}
}

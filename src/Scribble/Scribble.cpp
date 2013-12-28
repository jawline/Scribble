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
	load("target.main();");
}

Scribble::~Scribble() {
}

void Scribble::execute() {

	double vmStart = getCPUTime();

	environment.execute(vmFuncName);

	double vmEnd = getCPUTime();

	environment.printState();

	printf("VM execution took time %f\n", vmEnd - vmStart);

}

void Scribble::load(std::string const& code) {

	//Write an initialization function based off the the parameters given
	std::string initCode = writeInit(packagePath, code);

	//Compile the scribble program using the default namespaces
	std::map<std::string, NamespaceType> names;

	//Generate the sys package
	generateSystemPackage(names);

	//Compile the program using the new __init__ package created, crash on any exceptions.
	try {
		names = Parser::compileText(initCode, "__init__", names);
	} catch (ParserException& e) {
		printf("Unfortunately a parser error occurred because %s.\n", e.what());
		return;
	}

	//Check that the __init__ code has compiled properly.
	if (names["__init__"].find("__init__") == names["__init__"].end()
			|| names["__init__"]["__init__"].type() != FunctionSetEntry
			|| names["__init__"]["__init__"].getFunctionSet().size() != 1
			|| names["__init__"]["__init__"].getFunctionSet()[0]->numArgs()
					!= 0) {
		printf("Init function did not create properly\n");
	}

	//Grab a reference to __init__.__init__ for execution
	API::SafeFunction toExecute =
			names["__init__"]["__init__"].getFunctionSet()[0];

	registerPackages(names, environment);

	vmFuncName = toExecute->getNamespace() + VM::vmNamespaceSeperator
			+ toExecute->getName();
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

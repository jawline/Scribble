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

Scribble::Scribble(std::string const& package) :
		sourceCode("") {
	packagePath = package;
	load();
}

Scribble::Scribble(std::string const& package, std::string const& src) {
	packagePath = package;
	sourceCode = src;
	load();
}

Scribble::~Scribble() {
}

SafeFunction findFunction(std::vector<API::APIValue> arguments,
		ScribbleCore::FunctionSet set) {

	std::vector<ScribbleCore::Type*> types;

	for (unsigned int i = 0; i < arguments.size(); i++) {
		types.push_back(arguments[i].getType());
	}

	for (unsigned int i = 0; i < set.size(); i++) {
		SafeFunction iter = set[i];

		bool matched = iter->getSignature().argumentsEqual(types);

		if (matched) {
			return set[i];
		}

	}

	return nullptr;
}

API::APIValue Scribble::execute(std::string function) {

	//Make empty args list
	std::vector<API::APIValue> args;

	//Execute function();
	return execute(function, args);
}

API::APIValue Scribble::execute(std::string function,
		std::vector<API::APIValue> arguments) {

	API::SafeFunction toExecute =
			findFunction(arguments,
					compiledPackages[ScribbleCore::Parser::getUniformPath(
							packagePath)][function].getFunctionSet());

	if (toExecute.get() == nullptr) {
		printf("Function %s does not exist\n", function.c_str());
		return API::APIValue();
	}

	std::string vmFuncName = toExecute->getNamespace()
			+ VM::vmNamespaceSeperator + toExecute->getName();

	//Push the arguments
	for (unsigned int i = 0; i < arguments.size(); i++) {
		arguments[i].pushToVM(&environment);
	}

	environment.execute(vmFuncName);
	environment.printState();

	API::APIValue result;

	if (!toExecute->getSignature().getReturnType()->type()->Equals(ScribbleCore::getVoidType())) {

		long val = 0;
		bool ref = 0;

		environment.getRegister(VM::vmReturnResultRegister, val, ref);

		if (ref) {

			result = API::APIValue(toExecute->getSignature().getReturnType()->type(),
					environment.getHeap().getType(val),
					environment.getHeap().getSmartPointer(val), val);

		} else {

			result = API::APIValue(toExecute->getSignature().getReturnType()->type(), val);

		}

	} else {
		result = API::APIValue();
	}

	return result;
}

void Scribble::load() {

	//Generate the sys package
	generateSystemPackage(compiledPackages);

	//Generate the console package
	generateConsolePackage(compiledPackages);

	if (sourceCode.length() == 0) {

		//Compile the Function
		compiledPackages = ScribbleCore::Parser::compile(packagePath,
				compiledPackages);

	} else {

		compiledPackages = ScribbleCore::Parser::compileText(sourceCode,
				packagePath, compiledPackages);

	}

	//Compile the virtual machine from the packages.
	registerPackages(compiledPackages, environment);
}

VM::VirtualMachine* Scribble::getEnvironment() {
	return &environment;
}

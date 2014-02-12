/*
 * Scribble.hpp
 *
 *  Created on: 27 Dec 2013
 *      Author: blake
 */

#ifndef SCRIBBLE_HPP_
#define SCRIBBLE_HPP_
#include <string>
#include <VM/VirtualMachine.hpp>
#include <Scribble/Parser/Parser.hpp>
#include <API/Value/APIValue.hpp>

/**
 * Wrapper class that is capable of loading and executing Scribble functions
 */

class Scribble {
private:

	/**
	 * Stores the loaded package name and path.
	 */

	std::string packageName;
	std::string packagePath;
	std::string sourceCode;

	/**
	 * The VM environment running the code.
	 */

	VM::VirtualMachine environment;

	/**
	 * Stores the compiled code
	 */

	std::map<std::string, NamespaceType> compiledPackages;

	/**
	 * Loads the package using code as init code.
	 */

	void load();

public:

	/**
	 * Loads, compiles and prepares the package for execution.
	 * Throws a parser exception if anything goes wrong.
	 */

	Scribble(std::string const& package);

	/**
	 * Compiles and prepares the package packageName by using the source code provided.
	 * Throws a parsing exception if anything goes wrong.
	 */

	Scribble(std::string const& packageName, std::string const& sourceCode);

	virtual ~Scribble();

	/**
	 * Get the virtual machine context which has the packages loaded into it.
	 */

	VM::VirtualMachine* getEnvironment() {
		return &environment;
	}

	/**
	 * Execute the function name with zero arguments ( Equivilent to execute(function, empty argument list); )
	 */

	API::APIValue execute(std::string function);

	/**
	 * Execute the given function with the specified arguments, if not function of
	 * that name which takes the specified arguments is found then an error will
	 * be thrown.
	 */

	API::APIValue execute(std::string function,
			std::vector<API::APIValue> arguments);
};

#endif /* SCRIBBLE_HPP_ */

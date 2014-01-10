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
	virtual ~Scribble();

	API::APIValue execute(std::string code);
};

#endif /* SCRIBBLE_HPP_ */

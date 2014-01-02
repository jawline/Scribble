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
	 * Stores the of the VM func to execute
	 */

	std::string vmFuncName;

	/**
	 * The VM environment on which the loaded package is stored.
	 */

	VM::VirtualMachine environment;

	/**
	 * Loads the package using code as init code.
	 */

	void load(std::string const& code);

public:

	/**
	 * Loads, compiles and prepares the package for execution.
         * Throws a parser exception if anything goes wrong.
	 */

	Scribble(std::string const& package);
	virtual ~Scribble();

	void execute();

	std::string writeInit(std::string const& package,
			std::string const& execStr);
};

#endif /* SCRIBBLE_HPP_ */

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

	void execute(std::string code);

	std::string writeInit(std::string const& package,
			std::string const& execStr);
};

#endif /* SCRIBBLE_HPP_ */

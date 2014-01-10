/*
 * Console.cpp
 *
 *  Created on: 10 Jan 2014
 *      Author: blake
 */

#include <API/WriteFunction.hpp>
#include <API/ReadLine.hpp>
#include <Scribble/Value/TypeManager.hpp>
#include <Scribble/Parser/Parser.hpp>

void generateConsolePackage(std::map<std::string, NamespaceType>& all) {

	NamespaceType console;

	std::vector<SafeFunction> log;
	log.push_back(SmartPointer< Function > (new WriteFunction("console")));
	console["Log"] = NamespaceEntry(log);

	std::vector<SafeFunction> readLine;
	readLine.push_back(SmartPointer< Function > (new ReadLine("console")));
	console["ReadLine"] = NamespaceEntry(readLine);

	all["console"] = console;

}

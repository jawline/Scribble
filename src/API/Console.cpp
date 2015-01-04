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

void generateConsolePackage(std::map<std::string, ScribbleCore::NamespaceType>& all) {

    ScribbleCore::NamespaceType console;

    std::vector<SafeFunction> log;
    log.push_back(SafeFunction(new WriteFunction("console")));
    console["Log"] = ScribbleCore::NamespaceEntry(log);

    std::vector<SafeFunction> readLine;
    readLine.push_back(SafeFunction(new ReadLine("console")));
    console["ReadLine"] = ScribbleCore::NamespaceEntry(readLine);

    all["console"] = console;

}

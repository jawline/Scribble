/*
 * System.cpp
 *
 *  Created on: 26 Dec 2013
 *      Author: blake
 */

#include <API/WriteFunction.hpp>
#include <API/ReadLine.hpp>
#include <API/StringFunction.hpp>
#include <API/Modulo.hpp>
#include <API/RandomInt.hpp>
#include <API/Concat.hpp>
#include <API/Int.hpp>
#include <API/Float.hpp>
#include <API/Pow.hpp>
#include <Scribble/Parser/Parser.hpp>

void generateSystemPackage(std::map<std::string, NamespaceType>& builtin) {

	NamespaceType builtinFunctions;

	std::vector<SafeFunction> write;
	write.push_back(SmartPointer< Function > (new WriteFunction("sys")));
	builtinFunctions["Write"] = NamespaceEntry(write);

	std::vector<SafeFunction> concat;
	concat.push_back(SmartPointer< Function > (new Concat("sys")));
	builtinFunctions["Concat"] = NamespaceEntry(concat);

	std::vector<SafeFunction> intConvertor;
	intConvertor.push_back(SmartPointer< Function> ( new IntFromFloat32("sys")));
	builtinFunctions["Int"] = intConvertor;

	std::vector<SafeFunction> floatConvertor;
	floatConvertor.push_back(SmartPointer< Function> ( new Float32FromInt("sys")));
	builtinFunctions["Float32"] = floatConvertor;

	std::vector<SafeFunction> powInt;
	powInt.push_back(SmartPointer< Function> ( new Pow("sys")));
	builtinFunctions["PowInt"] = powInt;

	std::vector<SafeFunction> powFloat;
	powFloat.push_back(SmartPointer< Function> ( new PowFloat32("sys")));
	builtinFunctions["PowFloat"] = powFloat;

	std::vector<SafeFunction> string;
	string.push_back(SmartPointer< Function > (new IntToStringFunction("sys")));
	string.push_back(SmartPointer< Function > (new BoolToStringFunction("sys")));
	string.push_back(SmartPointer< Function > (new Float32ToStringFunction("sys")));
	builtinFunctions["String"] = NamespaceEntry(string);

	std::vector<SafeFunction> readLine;
	readLine.push_back(SP< Function > (new ReadLine("sys")));
	builtinFunctions["ReadLine"] = readLine;

	std::vector<SafeFunction> mod;
	mod.push_back(SP< Function > (new Modulo("sys")));
	builtinFunctions["Mod"] = NamespaceEntry(mod);

	std::vector<SafeFunction> randomInt;
	randomInt.push_back(SmartPointer< Function > (new RandomInt("sys")));
	builtinFunctions["RandomInt"] = NamespaceEntry(randomInt);

	builtin["sys"] = builtinFunctions;
}

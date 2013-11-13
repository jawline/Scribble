/**
 * Entry point for Scribble
 * @author Blake Loring
 */

#include <Scribble/Statement/Statement.hpp>
#include <Scribble/Value/StructureInfo.hpp>
#include <API/WriteFunction.hpp>
#include <API/ReadLine.hpp>
#include <API/StringFunction.hpp>
#include <API/Modulo.hpp>
#include <API/RandomInt.hpp>
#include <API/Concat.hpp>
#include <Scribble/Statement/Heap.hpp>
#include <Scribble/Parser/Parser.hpp>
#include <Scribble/Parser/ParserException.hpp>
#include <Scribble/Value/TypeManager.hpp>
#include <version_info.hpp>
#include <SASM/Parser.hpp>
#include <VM/VMNamespace.hpp>
#include <VM/OpCodes.hpp>
#include <VM/VirtualMachine.hpp>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cputime.hpp>

void generateBuiltinNamespace(std::map<std::string, NamespaceType>& builtin) {

	NamespaceType builtinFunctions;

	std::vector<SafeFunction> write;
	write.push_back(SmartPointer < Function > (new WriteFunction("sys")));
	builtinFunctions["Write"] = NamespaceEntry(write);

	std::vector<SafeFunction> concat;
	concat.push_back(SmartPointer < Function > (new Concat("sys")));
	builtinFunctions["Concat"] = NamespaceEntry(concat);

	std::vector<SafeFunction> string;
	string.push_back(
			SmartPointer < Function > (new IntToStringFunction("sys")));
	string.push_back(
			SmartPointer < Function > (new BoolToStringFunction("sys")));
	builtinFunctions["String"] = NamespaceEntry(string);

	std::vector<SafeFunction> readLine;
	readLine.push_back(SP < Function > (new ReadLine("sys")));
	builtinFunctions["ReadLine"] = readLine;

	std::vector<SafeFunction> mod;
	mod.push_back(SP < Function > (new Modulo("sys")));
	builtinFunctions["Mod"] = NamespaceEntry(mod);

	std::vector<SafeFunction> randomInt;
	randomInt.push_back(SmartPointer < Function > (new RandomInt("sys")));
	builtinFunctions["RandomInt"] = NamespaceEntry(randomInt);

	builtin["sys"] = builtinFunctions;
}

void registerEntireNamespace(std::map<std::string, NamespaceType>& allNames,
		VM::VirtualMachine& vm) {

	for (auto selectedNamespaceIter = allNames.begin();
			selectedNamespaceIter != allNames.end(); selectedNamespaceIter++) {

		vm.logMessage(VM::Log, std::string("Registering namespace ") + selectedNamespaceIter->first + std::string("\n"));

		VM::VMNamespace newSpace;

		NamespaceType names = selectedNamespaceIter->second;

		for (auto iterator = names.begin(); iterator != names.end();
				iterator++) {

			if (iterator->second.type() == FunctionSetEntry) {

				FunctionSet functionSet = iterator->second.getFunctionSet();

				for (unsigned int i = 0; i < functionSet.size(); i++) {
					SP<Function> function = functionSet[i];

					std::stringstream code;
					function->debugCode(code);

					newSpace[function->getName()] = VM::NamespaceEntry(function->generateVMFunction());

					vm.logMessage(VM::Log, std::string("Registered string ") + function->getName());

					vm.logMessage(VM::Log, std::string(" {\n") + code.str() + std::string("\n}\n"));
				}

			} else if (iterator->second.type() == TypeEntry) {

				vm.logMessage(VM::Log, std::string("Registering Type ") + iterator->first + "\n");

				TypeReference type = iterator->second.getType();
				StructureInfo* info = (StructureInfo*) iterator->second.getType()->type;

				for (unsigned int i = 0; i < info->getNumIndexs(); i++) {
					vm.logMessage(VM::Log, std::string("Registering field ") + info->getIndex(i).first + "\n");
				}

				vm.logMessage(VM::Log, "\n");

			}

		}

		vm.registerEntry(selectedNamespaceIter->first,
				VM::NamespaceEntry(newSpace));

	}

}

int main(int argc, char** argv) {

	srand(time(0));

	printf("Scribble %i.%i.%i\n", VERSION_MAJOR, VERSION_MINOR,
			VERSION_BUILD_NUMBER);

	if (argc != 2) {
		printf("Expected usage %s filename\n", argv[0]);
		return -1;
	}

	std::map<std::string, NamespaceType> names;
	generateBuiltinNamespace(names);

	VM::VirtualMachine vm;

	try {

		names = Parser::compile(argv[1], names);

	} catch (ParserException& e) {

		printf("Unfortunately a parser error occurred because %s.\n", e.what());

		return -1;
	}

	registerEntireNamespace(names, vm);

	char* packageName = strrchr(argv[1], '/');

	if (!packageName) {
		packageName = argv[1];
	} else {
		packageName++;
	}

	printf("Tree execution of %s\n", packageName);

	double treeStart = getCPUTime();

	valueHeap.free(
			names[packageName]["main"].getFunctionSet()[0]->execute(
					std::vector<Value*>()));

	double treeEnd = getCPUTime();

	printf("Now in the VM\n");

	double vmStart = getCPUTime();

	vm.execute(std::string(packageName) + ".main#0");

	double vmEnd = getCPUTime();

	vm.printState();

	printf("Tree to %f time. VM took %f time\n", treeEnd - treeStart,
			vmEnd - vmStart);

	printf("Exit\n");

	return 0;
}

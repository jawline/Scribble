/**
 * Entry point for Scribble
 * @author Blake Loring
 */

#include <Scribble/Statement/Statement.hpp>
#include <Scribble/Function/WriteFunction.hpp>
#include <Scribble/Function/ReadLine.hpp>
#include <Scribble/Function/StringFunction.hpp>
#include <Scribble/Function/Modulo.hpp>
#include <Scribble/Function/RandomInt.hpp>
#include <Scribble/Statement/Heap.hpp>
#include <Scribble/Parser/Parser.hpp>
#include <Scribble/Parser/ParserException.hpp>
#include <Scribble/Value/TypeManager.hpp>
#include <version_info.hpp>
#include <SASM/Parser.hpp>
#include <VM/OpCodes.hpp>
#include <VM/VirtualMachine.hpp>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cputime.hpp>

void generateBuiltinNamespace(std::map<std::string, NamespaceType> builtin) {

	NamespaceType builtinFunctions;

	std::vector<SafeFunction> write;
	write.push_back(SmartPointer<Function>(new WriteFunction()));
	builtinFunctions["Write"] = NamespaceEntry(write);

	std::vector<SafeFunction> string;
	string.push_back(SmartPointer<Function>(new IntToStringFunction()));
	string.push_back(SmartPointer<Function>(new BoolToStringFunction()));
	builtinFunctions["String"] = NamespaceEntry(string);

	std::vector<SafeFunction> readLine;
	readLine.push_back(SP<Function>(new ReadLine()));
	builtinFunctions["ReadLine"] = readLine;

	std::vector<SafeFunction> mod;
	mod.push_back(new Modulo());
	builtinFunctions["Mod"] = NamespaceEntry(mod);

	std::vector<SafeFunction> randomInt;
	randomInt.push_back(SmartPointer<Function>(new RandomInt()));
	builtinFunctions["RandomInt"] = NamespaceEntry(randomInt);

	std::map<std::string, NamespaceType> builtinNamespaces;

	builtin["sys"] = builtinFunctions;
}

void registerEntireNamespace(NamespaceType& names, VM::VirtualMachine& vm) {

	for (auto iterator = names.begin(); iterator != names.end(); iterator++) {

		if (iterator->second.type() == FunctionSetEntry) {

			FunctionSet functionSet = iterator->second.getFunctionSet();

			for (unsigned int i = 0; i < functionSet.size(); i++) {

				SP<Function> function = functionSet[i];

				std::stringstream code;
				function->debugCode(code);
				//printf("Compiled %s\n", code.str().c_str());

				VM::InstructionSet instructions = SimpleASM::Parser::parse(
						code.str().c_str());

				std::stringstream name;
				name << iterator->first << "#" << i;

				vm.registerFunction(VM::VMFunc(name.str(), instructions));

				printf("Registered function %s\n", name.str().c_str());
			}

		} else {
			printf("Registering type %s\n", iterator->first.c_str());
		}

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

	std::map<std::string, NamespaceType> builtin;
	generateBuiltinNamespace(builtin);

	printf("Entry\n");

	VM::VirtualMachine vm;

	NamespaceType names;

	try {
		names = Parser::compile(argv[1], builtin);
	} catch (ParserException& e) {
		printf("Unfortunately a parser error occurred because %s.\n", e.what());
		return -1;
	}

	registerEntireNamespace(names, vm);

	printf("Done prepairing bytecode for execution\n");

	double treeStart = getCPUTime();
	valueHeap.free(
			names["main"].getFunctionSet()[0]->execute(std::vector<Value*>()));
	double treeEnd = getCPUTime();

	printf("Now in the VM\n");

	double vmStart = getCPUTime();

	vm.execute("main#0");

	double vmEnd = getCPUTime();

	printf("Tree to %f time. VM took %f time\n", treeEnd - treeStart,
			vmEnd - vmStart);

	printf("Exit\n");

	return 0;
}

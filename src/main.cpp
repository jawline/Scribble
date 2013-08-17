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

int main(int argc, char** argv) {

	srand(time(0));

	printf("Scribble %i.%i.%i\n", VERSION_MAJOR, VERSION_MINOR,
			VERSION_BUILD_NUMBER);

	if (argc != 2) {
		printf("Expected usage %s filename\n", argv[0]);
		return -1;
	}

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
	builtinNamespaces["sys"] = builtinFunctions;

	printf("Entry\n");

	try {

		VM::VirtualMachine vm;

		auto names = Parser::compile(argv[1], builtinNamespaces);

		for (auto iterator = names.begin(); iterator != names.end(); iterator++) {
			auto func = iterator->second.getFunctionSet()[0];

			std::stringstream r;
			func->debugCode(r);
			printf("Compiled %s\n", r.str().c_str());
			auto instructions = SimpleASM::Parser::parse(r.str().c_str());

			vm.registerFunction(VM::VMFunc(iterator->first, instructions));
			printf("Registered %s\n", iterator->first.c_str());
		}


		printf("Done prepairing bytecode for execution\n");

		double treeStart = getCPUTime();
		valueHeap.free(names["main"].getFunctionSet()[0]->execute(std::vector<Value*>()));
		double treeEnd = getCPUTime();

		printf("Now in the VM\n");

		double vmStart = getCPUTime();

		vm.execute("main");

		double vmEnd = getCPUTime();

		printf("Tree to %f time. VM took %f time\n", treeEnd - treeStart,
				vmEnd - vmStart);

	} catch (ParserException& e) {
		printf("Unfortunately a parser error occurred because %s.\n", e.what());
		return -1;
	}

	printf("Exit\n");

	/**
	 if (!entry.Null()) {

	 try {

	 double start = getCPUTime();
	 valueHeap.free(entry->execute(std::vector<Value*>()));
	 double end = getCPUTime();

	 printf(
	 "\n-----------------------------------\n%f seconds to execute.\n",
	 end - start);

	 } catch (StatementException& c) {

	 printf(
	 "Unfortunately an error occured during execution because %s.\n",
	 c.what());

	 }

	 } else {
	 printf(
	 "It appears that the main function was not declared within the scope");
	 }

	 valueHeap.freeAll(); */

	return 0;
}

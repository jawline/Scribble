/**
 * Entry point for Scribble
 * @author Blake Loring
 */

#include <Statement/Statement.hpp>
#include <Function/WriteFunction.hpp>
#include <Function/ReadLine.hpp>
#include <Function/StringFunction.hpp>
#include <Function/Modulo.hpp>
#include <Function/RandomInt.hpp>
#include <Statement/Heap.hpp>
#include <Parser/Parser.hpp>
#include <Parser/ParserException.hpp>
#include <version_info.hpp>
#include <Value/TypeManager.hpp>
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

	/**
	 auto instructions = SimpleASM::Parser::parse(
	 "load 25 $6 #1\n"
	 "load 100000 $7 #2\n"
	 "load 0 $8 #3\n"
	 "add $6 25 $6 #4\n"
	 "add $6 150 $6 #5\n"
	 "add $8 1 $8 #6\n"
	 "lt $6 $7 #7\n"
	 "jump 3 #8\n"
	 "ret #9\n");

	 printf("Prepairing bytecode for execution\n");

	 VM::VirtualMachine vm;
	 vm.execute(instructions);*/

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

	SP<Function> entry;

	printf("Entry\n");

	try {

		entry =
				Parser::compile(argv[1], builtinNamespaces)["main"].getFunctionSet()[0];

		printf("Compiled %s\n", entry->debugCode().c_str());

		auto instructions = SimpleASM::Parser::parse(entry->debugCode());

		printf("Prepairing bytecode for execution\n");

		VM::VirtualMachine vm;
		vm.execute(instructions);

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

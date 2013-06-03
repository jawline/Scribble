/**
 * Entry point for Scribble
 * @author Blake Loring
 */

#include <Statement/Statement.hpp>
#include <Function/WriteFunction.hpp>
#include <Function/StringFunction.hpp>
#include <Function/Modulo.hpp>
#include <Function/RandomInt.hpp>
#include <Statement/Heap.hpp>
#include <Parser/Parser.hpp>
#include <Parser/ParserException.hpp>
#include <version_info.hpp>
#include <Value/TypeManager.hpp>
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
	 std::vector<VM::Instruction> inst;

	 inst.push_back(VM::Instruction(VM::OpPush, valueHeap.make(10)));
	 inst.push_back(VM::Instruction(VM::OpPush, valueHeap.make(10)));
	 inst.push_back(VM::Instruction(VM::OpAdd, nullptr));
	 inst.push_back(VM::Instruction(VM::OpPop, nullptr));
	 inst.push_back(VM::Instruction(VM::OpJump, valueHeap.make(0)));

	 VM::VirtualMachine vm;
	 vm.execute(0, inst);
	 */

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

	std::vector<SafeFunction> mod;
	mod.push_back(new Modulo());
	builtinFunctions["Mod"] = NamespaceEntry(mod);

	std::vector<SafeFunction> randomInt;
	randomInt.push_back(SmartPointer<Function>(new RandomInt()));
	builtinFunctions["RandomInt"] = NamespaceEntry(randomInt);

	std::map<std::string, NamespaceType> builtinNamespaces;
	builtinNamespaces["sys"] = builtinFunctions;

	SP<Function> entry;

	try {
		entry =
				Parser::compile(argv[1], builtinNamespaces)["main"].getFunctionSet()[0];
	} catch (ParserException& e) {
		printf("Unfortunately a parser error occurred because %s.\n", e.what());
		return -1;
	}

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

	valueHeap.freeAll();

	return 0;
}

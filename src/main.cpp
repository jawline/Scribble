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
#include <VM/SAsm.hpp>
#include <VM/OpCodes.hpp>
#include <VM/VirtualMachine.hpp>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cputime.hpp>

void Set(uint8_t* inst, int& current, uint8_t val) {
	inst[current++] = val;
}

void Set(uint8_t* inst, int& current, int val) {
	((int*) inst)[current] = val;
	current += 4;
}

void Set(uint8_t* inst, int& current, long lval) {
	*((long*) (inst + current)) = lval;
	current += sizeof(long);
}

int main(int argc, char** argv) {
	srand(time(0));

	printf("Scribble %i.%i.%i\n", VERSION_MAJOR, VERSION_MINOR,
			VERSION_BUILD_NUMBER);

	uint8_t inst[100];
	int current = 0;

	SimpleASM::SAsm::parse("hello\nworld\ntest\ning");

	Set(inst, current, (uint8_t) VM::OpLoadRegister);
	Set(inst, current, (uint8_t) 15);
	Set(inst, current, 1L);

	Set(inst, current, (uint8_t) VM::OpLoadRegister);
	Set(inst, current, (uint8_t) 1);
	Set(inst, current, 0L);

	long loopmarker = current;

	Set(inst, current, (uint8_t) VM::OpLoadRegister);
	Set(inst, current, (uint8_t) 14);
	Set(inst, current, loopmarker + 10);

	Set(inst, current, (uint8_t) VM::OpAddLong);
	Set(inst, current, (uint8_t) 1);
	Set(inst, current, (uint8_t) 15);

	Set(inst, current, (uint8_t) VM::OpTestLongNotEqual);
	Set(inst, current, (uint8_t) 14);
	Set(inst, current, (uint8_t) 1);
	Set(inst, current, 10000L);

	VM::VirtualMachine vm;
	VM::InstructionSet instructions(inst, current, 0);
	vm.execute(instructions);

	/*
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
	 */

	return 0;
}

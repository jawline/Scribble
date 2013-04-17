/**
 * Entry point for Scribble
 * @author Blake Loring
 */

#include <Statement/Statement.hpp>
#include <Function/WriteFunction.hpp>
#include <Function/StringFunction.hpp>
#include <Function/RandomInt.hpp>
#include <Statement/Heap.hpp>
#include <Parser/Parser.hpp>
#include <version_info.hpp>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char** argv) {
	srand(time(0));

	printf("Scribble %i.%i.%i\n", VERSION_MAJOR, VERSION_MINOR,
			VERSION_BUILD_NUMBER);

	if (argc != 2) {
		printf("Expected usage %s filename\n", argv[0]);
		return -1;
	}

	NamespaceType builtinFunctions;

	builtinFunctions["Write"].push_back(
			SmartPointer<Function>(new WriteFunction()));

	builtinFunctions["String"].push_back(
			SmartPointer<Function>(new IntToStringFunction()));

	builtinFunctions["String"].push_back(
			SmartPointer<Function>(new BoolToStringFunction()));

	builtinFunctions["RandomInt"].push_back(
			SmartPointer<Function>(new RandomInt()));

	Parser::setupNamespace("sys", builtinFunctions);

	SP<Function> entry = Parser::generateProgram(argv[1]);

	if (!entry.Null()) {
		clock_t startClocks = 0;
		clock_t endClocks = 0;

		startClocks = clock();
		delete entry->execute(std::vector<Value*>());
		endClocks = clock();

		printf("%ld clocks to execute. %f seconds to execute.\n",
				(endClocks - startClocks),
				((float) (endClocks - startClocks)) / CLOCKS_PER_SEC);
	} else {
		printf(
				"It appears that the main function was not declared within the scope");
	}

	valueHeap.freeAll();
}

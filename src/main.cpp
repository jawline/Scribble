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
#include <Value/TypeManager.hpp>
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

	builtinFunctions["Write"].push_back(
			SmartPointer<Function>(new WriteFunction()));

	builtinFunctions["String"].push_back(
			SmartPointer<Function>(new IntToStringFunction()));

	builtinFunctions["String"].push_back(
			SmartPointer<Function>(new BoolToStringFunction()));

	builtinFunctions["RandomInt"].push_back(
			SmartPointer<Function>(new RandomInt()));

	std::map<std::string, NamespaceType> builtinNamespaces;
	builtinNamespaces["sys"] = builtinFunctions;

	SP<Function> entry = Parser::compile(argv[1], builtinNamespaces)[0];

	if (!entry.Null()) {

		printf("Beginning execution\n");
		double start = getCPUTime();
		delete entry->execute(std::vector<Value*>());
		double end = getCPUTime();

		printf("%f seconds to execute.\n", end - start);
	} else {
		printf(
				"It appears that the main function was not declared within the scope");
	}

	valueHeap.freeAll();
}

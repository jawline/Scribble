/**
 * Entry point for Scribble
 * @author Blake Loring
 */

#include <Statement/Statement.hpp>
#include <Function/WriteFunction.hpp>
#include <Function/StringFunction.hpp>
#include <Function/RandomInt.hpp>
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
		double seconds = 0;

		seconds = clock();
		entry->execute(std::vector<Value*>());
		seconds = clock() - seconds;

		printf("%f seconds to execute.\n", seconds / CLOCKS_PER_SEC);
	} else {
		printf(
				"It appears that the main function was not declared within the scope");
	}
}

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

	NamespaceType builtinFunctions;

	builtinFunctions["Write"].push_back(
			SmartPointer<Function>(new WriteFunction()));

	builtinFunctions["String"].push_back(
			SmartPointer<Function>(new StringFunction()));

	builtinFunctions["RandomInt"].push_back(
			SmartPointer<Function>(new RandomInt()));

	Parser::setupNamespace("sys", builtinFunctions);

	SP<Function> entry = Parser::generateProgram(argv[1]);

	double seconds;

	seconds = clock();
	entry->execute(std::vector<Value*>());
	seconds = clock() - seconds;

	printf("%f seconds to execute.\n", seconds / CLOCKS_PER_SEC);
}

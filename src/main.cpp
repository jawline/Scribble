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
			VERSION_REVISION);

	std::map<std::string, SmartPointer<Function>> builtinFunctions;
	builtinFunctions["Write"] = SmartPointer<Function>(new WriteFunction());
	builtinFunctions["String"] = SmartPointer<Function>(new StringFunction());
	builtinFunctions["RandomInt"] = SmartPointer<Function>(new RandomInt());

	Parser::setupNamespace("System", builtinFunctions);

	SP<Function> entry = Parser::generateProgram(argv[1]);

	if (entry.Get() != 0) {
		entry->execute(std::vector<Value*>());
	} else {
		printf("Error\n");
	}
}

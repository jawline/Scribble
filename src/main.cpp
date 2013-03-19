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

	// Read the input file
	FILE* fin = fopen(argv[1], "r");

	// Run to the end of the file
	fseek(fin, 0, SEEK_END);

	// Get the length of the file
	size_t f_size = ftell(fin);
	fseek(fin, 0, SEEK_SET);
	char* buffer = new char[f_size];
	fread(buffer, 1, f_size, fin);
	fclose(fin);

	std::map<std::string, SmartPointer<Function>> builtinFunctions;
	builtinFunctions["Write"] = SmartPointer<Function>(new WriteFunction());
	builtinFunctions["String"] = SmartPointer<Function>(new StringFunction());
	builtinFunctions["RandomInt"] = SmartPointer<Function>(new RandomInt());
	SP<Function> entry = Parser::generateProgram(buffer, builtinFunctions);
	delete[] buffer;

	if (entry.Get() != 0) {
		entry->execute(std::vector<Value*>());
	} else {
		printf("Error\n");
	}
}

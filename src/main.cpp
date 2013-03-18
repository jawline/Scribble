/**
 * Entry point for Scribble
 * @author Blake Loring
 */

#include <Statement/Statement.hpp>
#include <Function/WriteFunction.hpp>
#include <Function/StringFunction.hpp>
#include <Parser/Parser.hpp>
#include <version_info.hpp>
#include <string.h>

int main(int argc, char** argv) {

	printf("Scribble %i.%i.%i\n", VERSION_MAJOR, VERSION_MINOR,
			VERSION_REVISION);

	printf("Buffering %s\n", argv[1]);

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

	printf("Parsing %s\n", argv[1]);

	SP<Function> entry = Parser::generateProgram(buffer, builtinFunctions);

	printf("Freeing Buffers\n");
	delete[] buffer;

	if (entry.Get()!=0) {
		printf("Executing\n");
		entry->execute(std::vector<Value*>());
	} else {
		printf("Error\n");
	}
}

#include <Statement/Statement.hpp>
#include <Parser/Parser.hpp>
#include <version_info.hpp>
#include <string.h>

void printHelp(char const* exeName) {
	printf("-- %s Usage --\n", exeName);
	printf("compile Input Output\n");
	printf("run File\n");
	printf("--------------\n");
}

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

	printf("Parsing %s\n", argv[1]);

	Function* entry = Parser::generateProgram(buffer);

	printf("Freeing Buffers\n");
	delete[] buffer;

	printf("Executing\n");
	entry->execute(std::vector<Value*>());
	delete entry;
}

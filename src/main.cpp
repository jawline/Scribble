/**
 * Entry point for Scribble
 * @author Blake Loring
 */

#include <iostream>
#include <algorithm>

/**
 * Version info defines the automatically generated scribble version.
 */

#include <version_info.hpp>
#include <Scribble/Scribble.hpp>

char const* getCmdOption(char ** begin, char ** end, char const* defaultOption,
		std::string option) {

	char ** itr = std::find(begin, end, option);

	if (itr != end && ++itr != end) {
		return *itr;
	}

	return defaultOption;
}

bool cmdOptionExists(char** begin, char** end, const std::string& option) {
	return std::find(begin, end, option) != end;
}

int main(int argc, char* argv[]) {
	srand(time(0));

	printf("Scribble %i.%i.%i\n", VERSION_MAJOR, VERSION_MINOR,
			VERSION_BUILD_NUMBER);

	if (!cmdOptionExists(argv, argv + argc, "--file")
			&& !cmdOptionExists(argv, argv + argc, "--exec")) {

		printf("Error, both --file and --exec are unset. Set either --file to --exec to continue\n");

		return -1;
	}

	char const* targetFile = getCmdOption(argv, argv + argc, "", "--file");

	Scribble environment(targetFile);
	environment.execute();

	return 0;
}

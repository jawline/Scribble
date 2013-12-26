/**
 * Entry point for Scribble
 * @author Blake Loring
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cputime.hpp>
#include <algorithm>

#include <Scribble/Statement/Statement.hpp>
#include <Scribble/Value/StructureInfo.hpp>
#include <Scribble/Statement/Heap.hpp>
#include <Scribble/Parser/Parser.hpp>
#include <Scribble/Parser/ParserException.hpp>
#include <Scribble/Value/TypeManager.hpp>
#include <SASM/Parser.hpp>
#include <VM/OpCodes.hpp>
#include <VM/VirtualMachine.hpp>

/**
 * Version info defines the automatically generated scribble version.
 */

#include <version_info.hpp>

/**
 * API/System defines the generateSystemPackage function which creates the sys library.
 */

#include <API/System.hpp>

#include <API/RegisterPackages.hpp>

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

std::string writeInit(std::string package, std::string thin,
		std::string execStr) {

	if (package.size() == 0) {
		std::string result = "package sys := import(\"sys\");\n";
		result += "func __init__() {\n";
		result += execStr;
		result += "}\n";
		return result;
	} else {
		std::string result =
				"package sys := import(\"sys\");\npackage target := import(\""
						+ package + "\");\n";
		result += "func __init__() {\n";
		result += execStr;
		result += "}\n";
		return result;
	}
}

int main(int argc, char* argv[]) {
	srand(time(0));

	printf("Scribble %i.%i.%i\n", VERSION_MAJOR, VERSION_MINOR,
			VERSION_BUILD_NUMBER);

	if (!cmdOptionExists(argv, argv + argc, "--file")
			&& !cmdOptionExists(argv, argv + argc, "--exec")) {
		printf(
				"Error, both --file and --exec are unset. Set either --file to --exec to continue\n");
		return -1;
	}

	char const* targetFile = getCmdOption(argv, argv + argc, "", "--file");

	//Calculate the name of the package being executed
	char const* packageName = strrchr(targetFile, '/');

	if (!packageName) {
		packageName = targetFile;
	} else {
		packageName++;
	}

	//The function to be executed, defaults to 'main'
	char const* execFunction = getCmdOption(argv, argv + argc,
			"target.main();\n", "--exec");

	//Write an initialization function based off the the parameters given
	std::string initCode = writeInit(targetFile, packageName, execFunction);

	//Compile the scribble program using the default namespaces
	std::map<std::string, NamespaceType> names;

	//Generate the sys package
	generateSystemPackage(names);

	//Compile the program using the new __init__ package created, crash on any exceptions.
	try {
		names = Parser::compileText(initCode, "__init__", names);
	} catch (ParserException& e) {
		printf("Unfortunately a parser error occurred because %s.\n", e.what());
		return -1;
	}

	//Check that the __init__ code has compiled properly.
	if (names["__init__"].find("__init__") == names["__init__"].end()
			|| names["__init__"]["__init__"].type() != FunctionSetEntry
			|| names["__init__"]["__init__"].getFunctionSet().size() != 1
			|| names["__init__"]["__init__"].getFunctionSet()[0]->numArgs()
					!= 0) {
		printf("Init function did not create properly\n");
	}

	//Grab a reference to __init__.__init__ for execution
	API::SafeFunction toExecute =
			names["__init__"]["__init__"].getFunctionSet()[0];

	VM::VirtualMachine vm;

	registerPackages(names, vm);

	char const* execMode = getCmdOption(argv, argv + argc, "vm", "--mode");

	if (strcmp(execMode, "vm") == 0) {

		double vmStart = getCPUTime();

		vm.execute(
				toExecute->getNamespace() + VM::vmNamespaceSeperator
						+ toExecute->getName());

		double vmEnd = getCPUTime();

		vm.printState();

		printf("VM execution took time %f\n", vmEnd - vmStart);

	} else if (strcmp(execMode, "tree") == 0) {

		double treeStart = getCPUTime();

		valueHeap.free(toExecute->execute(std::vector<Value*>()));

		double treeEnd = getCPUTime();

		printf("Tree execution took time %f\n", treeEnd - treeStart);

	} else {

		printf("Tree execution of %s\n", packageName);

		double treeStart = getCPUTime();

		valueHeap.free(toExecute->execute(std::vector<Value*>()));

		double treeEnd = getCPUTime();

		printf("Now in the VM\n");

		double vmStart = getCPUTime();

		vm.execute(
				toExecute->getNamespace() + VM::vmNamespaceSeperator
						+ toExecute->getName());

		double vmEnd = getCPUTime();

		vm.printState();

		printf("Tree to %f time. VM took %f time\n", treeEnd - treeStart,
				vmEnd - vmStart);

	}

	return 0;
}

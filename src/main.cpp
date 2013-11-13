/**
 * Entry point for Scribble
 * @author Blake Loring
 */

#include <Scribble/Statement/Statement.hpp>
#include <Scribble/Value/StructureInfo.hpp>
#include <API/WriteFunction.hpp>
#include <API/ReadLine.hpp>
#include <API/StringFunction.hpp>
#include <API/Modulo.hpp>
#include <API/RandomInt.hpp>
#include <API/Concat.hpp>
#include <Scribble/Statement/Heap.hpp>
#include <Scribble/Parser/Parser.hpp>
#include <Scribble/Parser/ParserException.hpp>
#include <Scribble/Value/TypeManager.hpp>
#include <version_info.hpp>
#include <SASM/Parser.hpp>
#include <VM/VMNamespace.hpp>
#include <VM/OpCodes.hpp>
#include <VM/VirtualMachine.hpp>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cputime.hpp>
#include <algorithm>

void generateBuiltinNamespace(std::map<std::string, NamespaceType>& builtin) {

	NamespaceType builtinFunctions;

	std::vector<SafeFunction> write;
	write.push_back(SmartPointer < Function > (new WriteFunction("sys")));
	builtinFunctions["Write"] = NamespaceEntry(write);

	std::vector<SafeFunction> concat;
	concat.push_back(SmartPointer < Function > (new Concat("sys")));
	builtinFunctions["Concat"] = NamespaceEntry(concat);

	std::vector<SafeFunction> string;
	string.push_back(
			SmartPointer < Function > (new IntToStringFunction("sys")));
	string.push_back(
			SmartPointer < Function > (new BoolToStringFunction("sys")));
	builtinFunctions["String"] = NamespaceEntry(string);

	std::vector<SafeFunction> readLine;
	readLine.push_back(SP < Function > (new ReadLine("sys")));
	builtinFunctions["ReadLine"] = readLine;

	std::vector<SafeFunction> mod;
	mod.push_back(SP < Function > (new Modulo("sys")));
	builtinFunctions["Mod"] = NamespaceEntry(mod);

	std::vector<SafeFunction> randomInt;
	randomInt.push_back(SmartPointer < Function > (new RandomInt("sys")));
	builtinFunctions["RandomInt"] = NamespaceEntry(randomInt);

	builtin["sys"] = builtinFunctions;
}

void registerEntireNamespace(std::map<std::string, NamespaceType>& allNames,
		VM::VirtualMachine& vm) {

	for (auto selectedNamespaceIter = allNames.begin();
			selectedNamespaceIter != allNames.end(); selectedNamespaceIter++) {

		vm.logMessage(VM::Log, std::string("Registering namespace ") + selectedNamespaceIter->first + std::string("\n"));

		VM::VMNamespace newSpace;

		NamespaceType names = selectedNamespaceIter->second;

		for (auto iterator = names.begin(); iterator != names.end();
				iterator++) {

			if (iterator->second.type() == FunctionSetEntry) {

				FunctionSet functionSet = iterator->second.getFunctionSet();

				for (unsigned int i = 0; i < functionSet.size(); i++) {
					SP<Function> function = functionSet[i];

					std::stringstream code;
					function->debugCode(code);

					newSpace[function->getName()] = VM::NamespaceEntry(function->generateVMFunction());

					vm.logMessage(VM::Log, std::string("Registered string ") + function->getName());

					vm.logMessage(VM::Log, std::string(" {\n") + code.str() + std::string("\n}\n"));
				}

			} else if (iterator->second.type() == TypeEntry) {

				vm.logMessage(VM::Log, std::string("Registering Type ") + iterator->first + "\n");

				TypeReference type = iterator->second.getType();
				StructureInfo* info = (StructureInfo*) iterator->second.getType()->type;

				for (unsigned int i = 0; i < info->getNumIndexs(); i++) {
					vm.logMessage(VM::Log, std::string("Registering field ") + info->getIndex(i).first + "\n");
				}

				vm.logMessage(VM::Log, "\n");

			}

		}

		vm.registerEntry(selectedNamespaceIter->first,
				VM::NamespaceEntry(newSpace));

	}

}

char const* getCmdOption(char ** begin, char ** end, char const* defaultOption, std::string option)
{

    char ** itr = std::find(begin, end, option);

    if (itr != end && ++itr != end)
    {
        return *itr;
    }

    return defaultOption;
}

bool cmdOptionExists(char** begin, char** end, const std::string& option)
{
    return std::find(begin, end, option) != end;
}

std::string writeInit(std::string package, std::string thin, std::string execStr) {

	if (package.size() == 0) {
		std::string result = "import(\"sys\");\n";
		result += "func __init__() {\n";
		result += execStr;
		result += "}\n";
		return result;
	} else {
		std::string result = "import(\"sys\");\nimport(\"" + package + "\");\n";
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

	if (!cmdOptionExists(argv, argv + argc, "--file") && !cmdOptionExists(argv, argv + argc, "--exec")) {
		printf("Error, both --file and --exec are unset. Set either --file to --exec to continue\n");
		return -1;
	}

	char const* targetFile = getCmdOption(argv, argv+argc, "", "--file");

	//Calculate the name of the package being executed
	char const* packageName = strrchr(targetFile, '/');

	if (!packageName) {
		packageName = targetFile;
	} else {
		packageName++;
	}

	//The function to be executed, defaults to 'main'
	char const* execFunction = getCmdOption(argv, argv + argc, (std::string(packageName)+".main();").c_str(), "--exec");

	//Compile the scribble program using the default namespaces
	std::map<std::string, NamespaceType> names;

	generateBuiltinNamespace(names);

	try {
		names = Parser::compileText(writeInit(targetFile, packageName, execFunction), "__init__", names);
	} catch (ParserException& e) {
		printf("Unfortunately a parser error occurred because %s.\n", e.what());
		return -1;
	}

	if (names["__init__"].find("__init__") == names["__init__"].end() || names["__init__"]["__init__"].type() != FunctionSetEntry || names["__init__"]["__init__"].getFunctionSet().size() != 1 || names["__init__"]["__init__"].getFunctionSet()[0]->numArgs() != 0) {
		printf("Init function did not create properly\n");
	}

	API::SafeFunction toExecute = names["__init__"]["__init__"].getFunctionSet()[0];

			printf("Tree execution of %s\n", packageName);

			double treeStart = getCPUTime();

			valueHeap.free(
					toExecute->execute(
							std::vector<Value*>()));

			double treeEnd = getCPUTime();

			printf("Now in the VM\n");

	
			VM::VirtualMachine vm;

			registerEntireNamespace(names, vm);

			double vmStart = getCPUTime();

			vm.execute(toExecute->getNamespace() + "." + toExecute->getName());

			double vmEnd = getCPUTime();

			vm.printState();

			printf("Tree to %f time. VM took %f time\n", treeEnd - treeStart,
					vmEnd - vmStart);

	/**
	if (names[packageName].find(execFunction) != names[packageName].end() && names[packageName][execFunction].type() == FunctionSetEntry && names[packageName][execFunction].getFunctionSet().size() > 0) {

		bool selected = false;
		API::SafeFunction toExecute;

		for (unsigned int i = 0; i < names[packageName][execFunction].getFunctionSet().size(); i++) {

			if (names[packageName][execFunction].getFunctionSet()[i]->numArgs() == 0) {
				selected = true;
				toExecute = names[packageName][execFunction].getFunctionSet()[i];
			}

		}

		if (!selected) {
			printf("There is no version of %s that takes zero arguments\n", execFunction);
		} else {
			printf("Tree execution of %s\n", packageName);

			double treeStart = getCPUTime();

			valueHeap.free(
					toExecute->execute(
							std::vector<Value*>()));

			double treeEnd = getCPUTime();

			printf("Now in the VM\n");

	
			VM::VirtualMachine vm;

			registerEntireNamespace(names, vm);

			double vmStart = getCPUTime();

			vm.execute(toExecute->getNamespace() + "." + toExecute->getName());

			double vmEnd = getCPUTime();

			vm.printState();

			printf("Tree to %f time. VM took %f time\n", treeEnd - treeStart,
					vmEnd - vmStart);
		}

	} else {
		printf("Function %s() was not declared in %s\n", execFunction, packageName);
	} */

	printf("Exit\n");

	return 0;
}

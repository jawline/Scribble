/**
 * Entry point for Scribble
 * Blake Loring
 */
#include <iostream>
#include <algorithm>

/**
 * Version info defines the automatically generated scribble version.
 */
#include <version_info.hpp>
#include <Scribble/Scribble.hpp>

/**
 * Defines clock
 */
#include <time.h>

/**
 * In this case that the Function files to compile ParserException will be thrown.
 */
#include <Scribble/Parser/ParserException.hpp>
#include <Arguments/ArgumentsParser.hpp>

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

bool isOption(std::string const& str) {

    //Check if str starts with -, if it is then its an option
    if (str.compare(0, 1, "-") == 0) {
        return true;
    }

    return false;
}

bool cmdFlagSet(char** begin, char** end, std::string const& option) {
    return cmdOptionExists(begin, end, option);
}

bool cmdBoolSet(char** begin, char** end, bool defaultOption,
                std::string const& option) {
    return std::string("true").compare(
               getCmdOption(begin, end, defaultOption ? "true" : "false", option))
           == 0;
}

bool lastOptionFile(char** begin, char** end, int argc) {

    if (argc < 2) {
        return false;
    }

    return !isOption(std::string(*(end - 1)));
}

void printUsage(char** argv, int argc) {

    char const* exe = argc < 1 ? "scribble" : *argv;

    printf("Usage: %s [OPTIONS] file\n", exe);
    printf("Options:\n-v --version: version information\n-r --runtime: output the time it takes for a script to execute\n");
}

int main(int argc, char** argv) {
    srand(time(0));

    if (cmdFlagSet(argv, argv + argc, "-v")
            || cmdFlagSet(argv, argv + argc, "--version")) {
        printf("Scribble %i.%i.%i\n", VERSION_MAJOR, VERSION_MINOR,
               VERSION_BUILD_NUMBER);
        return 0;
    }

    if (!lastOptionFile(argv, argv + argc, argc)) {
        printf("Error: No script specified\n");
        printUsage(argv, argc);
        return -1;
    }

    char const* targetFile = *(argv + (argc - 1));
    
    try {
        Scribble environment(targetFile);
        clock_t start = clock();
        API::APIValue val = environment.execute("main");
        clock_t end = clock();

        if (cmdFlagSet(argv, argv + argc, "-r")
                || cmdFlagSet(argv, argv + argc, "--runtime")) {
            printf("VM execution took time %f\n",
                   ((double) (end - start)) / (double) CLOCKS_PER_SEC);
        }
    } catch (ScribbleCore::ParserException& ex) {
        printf("Error: %s\n", ex.what());
    }

    return 0;
}

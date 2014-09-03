/*
 * ArgumentsParser.cpp
 *
 *  Created on: 3 Sep 2014
 *      Author: blake
 */

#include "ArgumentsParser.hpp"
#include <string.h>

namespace ScribbleExtra {

ArgumentsParser::ArgumentsParser(int argc, char** argv) {
	parse(argc, argv);

}

ArgumentsParser::~ArgumentsParser() {
}

void ArgumentsParser::parse(int argc, char** argv) {

	for (int i = 0; i < argc; i++) {

		if (strncmp(argv[i], "-", 1) == 0 && strncmp(argv[i], "--", 2) != 0) {

			if (i + 1 < argc) {
				printf("%s %s\n", argv[i] + 1, argv[i + 1]);
				namedArguments_.push_back(Argument(argv[i] + 1, argv[i + 1]));
			}

			i++;
		} else if (strncmp(argv[i], "--", 2) == 0) {

			if (i + 1 < argc) {
				printf("%s %s\n", argv[i] + 2, argv[i + 1]);
				namedArguments_.push_back(Argument(argv[i] + 2, argv[i + 1]));
			}

			i++;
		} else {
			printf("%s\n", argv[i]);
			unnamedArguments_.push_back(Argument(argv[i]));
		}

	}

}

Argument const& ArgumentsParser::get(unsigned int id) const {
	return unnamedArguments_[id];
}

unsigned int ArgumentsParser::getNumArguments() const {
	return unnamedArguments_.size();
}

Argument const ArgumentsParser::search(std::string const& name) const {

	for (unsigned int i = 0; i < namedArguments_.size(); i++) {

		if (namedArguments_[i].getName().compare("name") == 0) {
			return namedArguments_[i];
		}

	}

	return Argument("", "");
}

Argument const ArgumentsParser::search(std::string const& name,
		std::string const& alternative) const {

	if (exists(name)) {
		return search(name);
	}

	if (exists(alternative)) {
		return search(alternative);
	}

	return Argument("", "");
}

bool ArgumentsParser::exists(std::string const& name) const {
	return search(name).getName().compare("") == 0 ? false : true;
}

bool ArgumentsParser::exists(std::string const& name, std::string const& alternative) const {

	if (exists(name)) {
		return true;
	}

	if (exists(alternative)) {
		return true;
	}

	return false;
}

} /* namespace ScribbleCore */

/*
 * ArgumentsParser.hpp
 *
 *  Created on: 3 Sep 2014
 *      Author: blake
 */

#ifndef ARGUMENTSPARSER_HPP_
#define ARGUMENTSPARSER_HPP_
#include <vector>
#include <string>

namespace ScribbleExtra {

class Argument {
  public:

    enum ArgumentType {
        Named, Unnamed
    };

    Argument(std::string value) :
        type_(Unnamed), value_(value) {

    }

    Argument(std::string name, std::string value) :
        type_(Named), name_(name), value_(value) {
    }

    ArgumentType getType() const {
        return type_;
    }

    std::string const& getName() const {
        return name_;
    }

    std::string const& getValue() const {
        return value_;
    }

  private:

    ArgumentType type_;
    std::string name_;
    std::string value_;

};

class ArgumentsParser {
  private:
    std::vector<Argument> unnamedArguments_;
    std::vector<Argument> namedArguments_;

    void parse(int argc, char** argv);

  public:
    ArgumentsParser(int argc, char** argv);
    virtual ~ArgumentsParser();

    /**
     * Searches for a named argument from the named arguments list
     */
    Argument const search(std::string const& name) const;

    /**
     * Returns the first argument found with one of either two names (Useful for -v or --version)
     */
    Argument const search(std::string const& name,
                          std::string const& alternative) const;

    /**
     * Returns true if an argument with the following name exists
     */
    bool exists(std::string const& name) const;

    /**
     * Returns true if there is one argument of either name
     */
    bool exists(std::string const& name, std::string const& alternative) const;

    /**
     * Returns an argument from the unnamed arguments list
     */
    Argument const& get(unsigned int id) const;

    /**
     * Get the number of unnamed arguments
     */
    unsigned int getNumArguments() const;

};

} /* namespace ScribbleExtra */
#endif /* ARGUMENTSPARSER_HPP_ */

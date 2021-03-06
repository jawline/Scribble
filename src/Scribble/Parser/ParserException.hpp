/*
 * ParserException.hpp
 *
 *  Created on: 28 Mar 2013
 *      Author: blake
 */

#ifndef PARSEREXCEPTION_HPP_
#define PARSEREXCEPTION_HPP_
#include <exception>
#include <string>

namespace ScribbleCore {

/**
 * ParserException
 * thrown whenever an exception occurs during the parsing of a program.
 * Contains information about which file was currently being parser, what the details where and where it happened.
 */

class ParserException: public std::exception {
  private:
    std::string file_;
    std::string details_;
    std::string error_;

  public:
    ParserException(std::string file, std::string details);
    virtual ~ParserException() throw ();
    virtual const char* what() const throw ();
};

}

#endif /* PARSEREXCEPTION_HPP_ */

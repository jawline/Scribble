/*
 * Util.hpp
 *
 *  Created on: 19 Mar 2013
 *      Author: blake
 */

#ifndef UTIL_HPP_
#define UTIL_HPP_
#include <string>

/**
 * This exception is thrown when the utility class is unable to create the specified type.
 */

class UtilException: public std::exception {
  private:

    /**
     * The reason why it cannot create the specified type.
     */

    std::string reason_;

  public:

    UtilException(std::string const& reason) throw ();
    virtual ~UtilException() throw ();

    virtual const char* what() const throw ();

};

#endif /* UTIL_HPP_ */

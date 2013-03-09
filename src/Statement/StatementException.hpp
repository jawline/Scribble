#ifndef _STATEMENT_EXCEPTION_H
#define _STATEMENT_EXCEPTION_H

#include <iostream>
#include <exception>
using namespace std;

class StatementException : public exception
{
  private:
	std::string error_;

  public:
  StatementException(std::string error) {
	error_ = error;
  }

  virtual const char* what() const throw()
  {
  	return error_.c_str();
  }
};

#endif //_STATEMENT_EXCEPTION_H

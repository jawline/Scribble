#ifndef _STATEMENT_EXCEPTION_H
#define _STATEMENT_EXCEPTION_H

#include <iostream>
#include <exception>
using namespace std;

class SasmException: public exception {
private:
	std::string error_;

public:
	SasmException(std::string error);
	virtual ~SasmException() throw ();

	virtual const char* what() const throw () {
		return error_.c_str();
	}
};

#endif //_STATEMENT_EXCEPTION_H

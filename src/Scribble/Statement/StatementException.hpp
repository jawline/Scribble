#ifndef _STATEMENT_EXCEPTION_H
#define _STATEMENT_EXCEPTION_H

#include <iostream>
#include <exception>
using namespace std;

namespace ScribbleCore {

class Statement;

class StatementException: public exception {
private:
	std::string error_;

public:
	StatementException(Statement* statement, std::string error);
	virtual ~StatementException() throw ();

	virtual const char* what() const throw () {
		return error_.c_str();
	}
};

/**
 * The statement assert function will throw a statement exception with
 * the given error if the boolean assertionValue is false
 */

void StatementAssert(Statement* statement, bool assertionValue,
		std::string error);

}

#endif //_STATEMENT_EXCEPTION_H

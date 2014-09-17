#include "StatementException.hpp"
#include "Statement.hpp"

namespace ScribbleCore {

StatementException::StatementException(Statement* statement,
		std::string error) {

	if (statement) {
		error_ = error + " at " + statement->generateDebugInformation();
	} else {
		error_ = error;
	}
}

StatementException::~StatementException() throw () {
}

void StatementAssert(Statement* statement, bool assertionValue,
		std::string error) {

	if (assertionValue) {
		throw StatementException(statement, error);
	}

}

}

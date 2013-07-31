#include "StatementException.hpp"
#include "Statement.hpp"

StatementException::StatementException(Statement* statement,
		std::string error) {

	if (statement) {
		error_ = error + " at " + statement->generateDebugInformation();
	} else {
		error_ = error;
	}
}

StatementException::~StatementException() throw() {
}

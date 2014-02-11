#include "IntStatement.hpp"
#include <sstream>
#include <Scribble/Statement/Heap.hpp>

IntStatement::IntStatement(int lineNo, std::string sym, int intValue) :
		Statement(lineNo, sym) {
	intValue_ = intValue;
}

void IntStatement::checkTree(Type* functionType) {

}

int IntStatement::generateCode(int resultRegister,
		std::stringstream& generated) {

	if (resultRegister != -1) {

		generated << "load " << intValue_ << " $" << resultRegister << " #"
				<< resultRegister << "\n";

	}

	return 1;
}

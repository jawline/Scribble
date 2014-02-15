#include "StringStatement.hpp"
#include <Scribble/Value/TypeManager.hpp>

namespace ScribbleCore {

StringStatement::StringStatement(int lineNo, std::string sym,
		std::string stringValue) :
		Statement(lineNo, sym) {
	stringValue_ = stringValue;
}

void StringStatement::checkTree(Type* functionType) {

}

int StringStatement::generateCode(int resultRegister,
		std::stringstream& generated) {
	generated << "load \"" << stringValue_ << "\" $" << resultRegister << "\n";
	return 1;
}

}

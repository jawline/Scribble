#include "StringStatement.hpp"
#include <Value/String.hpp>
#include <Statement/Heap.hpp>
#include <Value/TypeManager.hpp>

StringStatement::StringStatement(int lineNo, std::string sym, std::string stringValue) : Statement(lineNo, sym) {
	stringValue_ = stringValue;
}

Value* StringStatement::execute(std::vector<Value*> const& variables) {
	StringValue* gen = (StringValue*) valueHeap.make(getStringType());
	gen->setValue(stringValue_);
	return gen;
}

void StringStatement::checkTree(Type* functionType) {

}

int StringStatement::generateCode(int resultRegister, std::stringstream& generated) {
	generated << "load \"" << stringValue_ << "\" $" << resultRegister << "\n";
	return 1;
}

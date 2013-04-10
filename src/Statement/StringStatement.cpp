#include "StringStatement.hpp"
#include <Value/String.hpp>
#include <Statement/Heap.hpp>

StringStatement::StringStatement(int lineNo, std::string sym, std::string stringValue) : Statement(lineNo, sym) {
	stringValue_ = stringValue;
}

Value* StringStatement::execute(std::vector<Value*> const& variables) {
	StringValue* gen = (StringValue*) valueHeap.make(String);
	gen->setValue(stringValue_);
	return gen;
}

void StringStatement::checkTree(ValueType functionType) {

}

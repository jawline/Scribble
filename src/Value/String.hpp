#ifndef _STRING_H_
#define _STRING_H_
#include "Value.hpp"
#include <string>
#include <Statement/Heap.hpp>

class StringValue : public Value {
private:
	std::string value_;

public:

	StringValue(std::string const value);
	Type* type();
	Value* clone();

	void applyOperator(ValueOperator v, Value* r);

	std::string getValue();

	void setValue(std::string const& ref);
};

#endif //_STRING_H_

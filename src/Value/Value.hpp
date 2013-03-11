#ifndef _VALUE_H_
#define _VALUE_H_

enum ValueType {
 String,
 Int,
 Void
};

enum ValueOperator {
 Add,
 Subtract,
 Multiply,
 Divide
};

class Value {
private:

public:
	virtual ~Value() {}
	virtual void applyOperator(ValueOperator, Value* other) = 0;
	virtual ValueType type() = 0;
	virtual Value* clone() = 0;
};

#endif //_VALUE_H_

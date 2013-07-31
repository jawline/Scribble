#ifndef _VALUE_H_
#define _VALUE_H_
#include "Type.hpp"

// Enum defining all value operators (Add, Divide, Assign, Subtract, Mod etc)
enum ValueOperator {
	Assign, Add, Subtract, Multiply, Divide
};

/**
 * Value class from which all value types extend.
 */

class Value {
public:

	virtual ~Value() {
	}

	/**
	 * Apply the specified operator to the given value.
	 */
	virtual void applyOperator(ValueOperator, Value* other) = 0;

	/**
	 * Get the ValueType of the value
	 */
	virtual Type* type() = 0;

	/**
	 * Create an identical copy of the value
	 */
	virtual Value* clone() = 0;

};

#endif //_VALUE_H_

#ifndef _VALUE_DEF_H_
#define _VALUE_DEF_H_

class Value {
private:
	float floatValue_;

public:
	Value(float floatValue);
	Value();

	float FloatValue();

	Value Add(Value const& rhs) {
		return Value(floatValue_ += rhs.floatValue_);
	}

	Value Subtract(Value const& rhs) {
		return Value(floatValue_ -= rhs.floatValue_);
	}

	Value Multiply(Value const& rhs) {
		return Value(floatValue_ * rhs.floatValue_);
	}

	Value Divide(Value const& rhs) {
		return Value(floatValue_ / rhs.floatValue_);
	}
};

#endif //_VALUE_DEF_H_

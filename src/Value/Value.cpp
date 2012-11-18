#include "Value.hpp"

Value::Value(float v) {
	floatValue_ = v;
}

Value::Value() {
}

float Value::FloatValue() {
	return floatValue_;
}

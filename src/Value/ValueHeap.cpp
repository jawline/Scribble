/*
 * ValueHeap.cpp
 *
 *  Created on: 10 Apr 2013
 *      Author: blake
 */

#include "ValueHeap.hpp"
#include <Value/Util.hpp>
#include <Value/Bool.hpp>
#include <Value/Int.hpp>
#include <Value/TypeManager.hpp>

ValueHeap::ValueHeap() {

	valueStore_ = new Stack<Value*> [ValueTypeMax];

}

ValueHeap::~ValueHeap() {
	freeAll();
	delete[] valueStore_;
}

Value* ValueHeap::make(Type* type) {

	//If it is a complex type we don't store it so ignore it
	if (type->getSubtype() == nullptr) {
		if (valueStore_[type->getType()].size() > 0) {
			return valueStore_[type->getType()].pop();
		}
	}

	return ValueUtil::generateValue(type);
}

Value* ValueHeap::make(bool value) {
	Value* val = make(getBooleanType());
	((BoolValue*) val)->setValue(value);
	return val;
}

Value* ValueHeap::make(int value) {
	Value* val = make(getIntType());
	((IntValue*) val)->setValue(value);
	return val;
}

void ValueHeap::free(Value* v) {

	if (valueStore_[v->type()->getType()].size() < ValueStackMax) {
		valueStore_[v->type()->getType()].push(v);
	} else {
		delete v;
	}

}

void ValueHeap::freeAll() {

	for (unsigned int i = 0; i < ValueTypeMax; ++i) {

		while (valueStore_[i].size() > 0) {
			delete valueStore_[i].pop();
		}

	}

}

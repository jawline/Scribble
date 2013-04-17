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

ValueHeap::ValueHeap() {

	valueStore_ = new Stack<Value*> [ValueTypeMax];

}

ValueHeap::~ValueHeap() {
	freeAll();
	delete[] valueStore_;
}

Value* ValueHeap::make(ValueType type) {

	if (valueStore_[type].size() > 0) {
		return valueStore_[type].pop();
	}

	return ValueUtil::generateValue(type);
}

Value* ValueHeap::make(bool value) {
	Value* val = make(Boolean);
	((BoolValue*) val)->setValue(value);
	return val;
}

Value* ValueHeap::make(int value) {
	Value* val = make(Int);
	((IntValue*) val)->setValue(value);
	return val;
}

void ValueHeap::free(Value* v) {

	if (valueStore_[v->type()].size() < ValueStackMax) {
		valueStore_[v->type()].push(v);
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

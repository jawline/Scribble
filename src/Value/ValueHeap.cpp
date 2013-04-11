/*
 * ValueHeap.cpp
 *
 *  Created on: 10 Apr 2013
 *      Author: blake
 */

#include "ValueHeap.hpp"
#include <Value/Util.hpp>

ValueHeap::ValueHeap() {

	valueStore_ = new std::stack<Value*>[ValueTypeMax];

}

ValueHeap::~ValueHeap() {

	for (unsigned int i = 0; i < ValueTypeMax; ++i) {
		for (unsigned int j = 0; j < valueStore_[i].size(); ++j) {
			delete valueStore_[j].top();
			valueStore_[j].pop();
		}
	}

	delete[] valueStore_;
}

Value* ValueHeap::make(ValueType type) {

	if (valueStore_[type].size() > 0) {
		Value* stored = valueStore_[type].top();
		valueStore_[type].pop();
		return stored;
	}

	return ValueUtil::generateValue(type);
}

void ValueHeap::free(Value* v) {

	if (valueStore_[v->type()].size() < ValueStackMax) {
		valueStore_[v->type()].push(v);
	} else {
		delete v;
	}
}

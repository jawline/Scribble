/*
 * ValueHeap.hpp
 *
 *  Created on: 10 Apr 2013
 *      Author: blake
 */

#ifndef VALUEHEAP_HPP_
#define VALUEHEAP_HPP_
#include <Value/Value.hpp>
#include <stack>

class ValueHeap {
private:
	std::stack<Value*>* valueStore_;
	const static unsigned int ValueStackMax = 50;

public:
	ValueHeap();
	virtual ~ValueHeap();

	Value* make(ValueType type);
	void free(Value* value);
	void freeAll();
};

#endif /* VALUEHEAP_HPP_ */

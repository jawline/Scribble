/*
 * ValueHeap.hpp
 *
 *  Created on: 10 Apr 2013
 *      Author: blake
 */

#ifndef VALUEHEAP_HPP_
#define VALUEHEAP_HPP_
#include <Value/Value.hpp>
#include <Stack/Stack.hpp>
#include <stack>

class ValueHeap {
private:
	Stack<Value*>* valueStore_;
	const static unsigned int ValueStackMax = 50;

public:
	ValueHeap();
	virtual ~ValueHeap();

	Value* make(Type* type);
	Value* make(bool value);
	Value* make(int value);
	void free(Value* value);
	void freeAll();
};

#endif /* VALUEHEAP_HPP_ */

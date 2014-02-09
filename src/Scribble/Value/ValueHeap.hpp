/*
 * ValueHeap.hpp
 *
 *  Created on: 10 Apr 2013
 *      Author: blake
 */

#ifndef VALUEHEAP_HPP_
#define VALUEHEAP_HPP_
#include <Scribble/Value/Value.hpp>
#include <Stack/Stack.hpp>
#include <stack>
#include <types.h>

/**
 * The value heap stores a bunch of primitive values which can are free to be reused without requiring a new.
 * It also acts as a facade to value creation.
 */

class ValueHeap {
private:
	Stack<Value*>* valueStore_;
	const static unsigned int ValueStackMax = 50;

public:
	ValueHeap();
	virtual ~ValueHeap();

	/**
	 * Get a value of a specified type.
	 */

	Value* make(Type* type);

	/**
	 * Get a boolean value class.
	 */

	Value* make(bool value);

	/**
	 * Get a int value class.
	 */

	Value* make(int value);

	/**
	 * Get a float32 value class.
	 */

	Value* make(float32_t value);

	/**
	 * Add the specified value back into the ValueHeap.
	 */

	void free(Value* value);

	/**
	 * Free all remaining values on the heap.
	 */

	void freeAll();
};

#endif /* VALUEHEAP_HPP_ */

/*
 * Heap.hpp
 *
 *  Created on: Jul 16, 2013
 *      Author: blake
 */

#ifndef HEAP_HPP_
#define HEAP_HPP_
#include "VMHeapEntry.hpp"
#include <stack>
#include <string>
#include <types.h>
#include <map>

//TODO: This will break at 4bn indexs created in a runtime. Do it cleaner

namespace VM {

class Heap {
private:
	std::vector<VMHeapEntry> heapItems_;
	std::stack<int> unusedIndexs_;

	bool lastFlagState_;

public:
	Heap();
	virtual ~Heap();

	/**
	 * Returns a value > 0 which acts as a reference to an element on the heap.
	 */

	long allocate(SmartPointer<VMEntryType> type, int size, uint8_t* initial);

	bool validReference(long entry);
	SmartPointer<VMEntryType> getType(long entry);
	uint8_t* getAddress(long entry);
	int getSize(long entry);

	void flag(long i);

	void lock(long i);
	void unlock(long i);

	/**
	 * This function deletes any unflagged heap elements and then sets flag states for the next garbage collector run
	 */

	int processUnflagged();

	std::string debugState();
};

} /* namespace VM */
#endif /* HEAP_HPP_ */

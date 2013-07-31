/*
 * Heap.hpp
 *
 *  Created on: Jul 16, 2013
 *      Author: blake
 */

#ifndef HEAP_HPP_
#define HEAP_HPP_
#include "VMHeapEntry.hpp"
#include <string>
#include <stdint.h>
#include <map>

//TODO: This will break at 4bn indexs created in a runtime. Do it cleaner

namespace VM {

class Heap {
private:
	std::map<int, VMHeapEntry> heapMap_;
	long lastIndex_;

public:
	Heap();
	virtual ~Heap();

	long allocate(SP<VMEntryType> type, int size, uint8_t* initial);

	bool validReference(long entry);
	SP<VMEntryType> getType(long entry);
	uint8_t* getAddress(long entry);
	int getSize(long entry);

	void flag(long i);
	void unflagAll();
	int deleteUnflagged();

	std::string debugState();
};

} /* namespace VM */
#endif /* HEAP_HPP_ */

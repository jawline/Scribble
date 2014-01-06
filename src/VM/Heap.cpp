/*
 * Heap.cpp
 *
 *  Created on: Jul 16, 2013
 *      Author: blake
 */

#include "Heap.hpp"
#include <sstream>
#include <vector>
#include <string.h>

namespace VM {

Heap::Heap() {
	lastFlagState_ = false;
}

Heap::~Heap() {
	// TODO Auto-generated destructor stub
}

bool Heap::validReference(long entry) {

	if (entry > heapItems_.size()) {
		return false;
	}

	if (heapItems_[entry].pointer == nullptr) {
		return false;
	}

	return true;
}

long Heap::allocate(SmartPointer<VMEntryType> type, int size, uint8_t* initial) {

	uint8_t* memory = new uint8_t[size];

	/**
	 * If initial is null then null all values instead of copying
	 */

	if (initial != nullptr) {

		for (int i = 0; i < size; ++i) {
			memory[i] = initial[i];
		}

	} else {

		memset(memory, 0, size);

	}

	VMHeapEntry entry;

	entry.type = type;
	entry.pointer = memory;
	entry.sizeBytes = size;
	entry.flagged = lastFlagState_;

	long index = 0;

	if (unusedIndexs_.empty()) {
		index = heapItems_.size();
		heapItems_.push_back(entry);
	} else {
		index = unusedIndexs_.top();
		unusedIndexs_.pop();
		heapItems_[index] = entry;
	}

	return index;
}

uint8_t* Heap::getAddress(long entry) {

	if (!validReference(entry)) {
		return nullptr;
	}

	return heapItems_[entry].pointer;
}

int Heap::getSize(long entry) {

	if (!validReference(entry)) {
		return -1;
	}

	return heapItems_[entry].sizeBytes;
}

SmartPointer<VMEntryType> Heap::getType(long entry) {

	if (!validReference(entry)) {
		return nullptr;
	}

	return heapItems_[entry].type;
}

void Heap::flag(long i) {

	if (validReference(i)) {

		//Flag it ensuring it won't be deleted the next time processUnflagged is called.
		heapItems_[i].flagged = !lastFlagState_;

	}

}

int Heap::processUnflagged() {

	std::vector < std::map<int, VMHeapEntry>::iterator > remove;

	for (unsigned int id = 0; id < heapItems_.size(); id++) {

		if (heapItems_[id].flagged == lastFlagState_ && heapItems_[id].pointer != nullptr) {
			delete[] heapItems_[id].pointer;
			heapItems_[id].pointer = nullptr;
			unusedIndexs_.push(id);
		}
	}

	//Flip last flag state. This allows us to monitor which heap variables are used without constantly cycling through every garbage collected element each time this is run.
	lastFlagState_ = !lastFlagState_;

	return remove.size();
}

std::string Heap::debugState() {
	std::stringstream dbg;
	dbg << "--HEAP DATA--\n";
	dbg << "Num heap entries: ";
	dbg << heapItems_.size() - unusedIndexs_.size();
	dbg << "\n";

	/**
	for (auto iter = heapMap_.begin(); iter != heapMap_.end(); iter++) {
		dbg << "Entry: " << iter->first << " type "
				<< iter->second.type->typeName();

		if (iter->second.type->typeName().compare("string") == 0) {
			dbg << " string value: " << iter->second.pointer;
		}

		dbg << "\n";
	}*/

	dbg << "--END HEAP--\n";
	return dbg.str();
}

} /* namespace VM */

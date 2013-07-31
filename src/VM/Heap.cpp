/*
 * Heap.cpp
 *
 *  Created on: Jul 16, 2013
 *      Author: blake
 */

#include "Heap.hpp"
#include <sstream>
#include <vector>

namespace VM {

Heap::Heap() {
	lastIndex_ = 1;
}

Heap::~Heap() {
	// TODO Auto-generated destructor stub
}

bool Heap::validReference(long entry) {
	auto it = heapMap_.find(entry);

	if (it == heapMap_.end()) {
		return false;
	}

	return true;
}

long Heap::allocate(SP<VMEntryType> type, int size, uint8_t* initial) {

	uint8_t* memory = new uint8_t[size];

	for (int i = 0; i < size; ++i) {
		memory[i] = initial[i];
	}

	VMHeapEntry entry;

	entry.type = type;
	entry.pointer = memory;
	entry.sizeBytes = size;

	long index = lastIndex_++;

	heapMap_[index] = entry;

	return index;
}

uint8_t* Heap::getAddress(long entry) {

	if (!validReference(entry)) {
		return nullptr;
	}

	return heapMap_[entry].pointer;
}

int Heap::getSize(long entry) {

	if (!validReference(entry)) {
		return -1;
	}

	return heapMap_[entry].sizeBytes;
}

SP<VMEntryType> Heap::getType(long entry) {

	if (!validReference(entry)) {
		return nullptr;
	}

	return heapMap_[entry].type;
}

void Heap::flag(long i) {

	if (validReference(i)) {
		heapMap_[i].flagged = true;
	}

}

void Heap::unflagAll() {

	for (auto iter = heapMap_.begin(); iter != heapMap_.end(); iter++) {
		iter->second.flagged = false;
	}

}

int Heap::deleteUnflagged() {

	std::vector<std::map<int, VMHeapEntry>::iterator> remove;

	for (auto iter = heapMap_.begin(); iter != heapMap_.end(); iter++) {

		if (!iter->second.flagged) {
			delete[] iter->second.pointer;
			remove.push_back(iter);
		}
	}

	for (unsigned int i = 0; i < remove.size(); i++) {
		heapMap_.erase(remove[i]);
	}

	return remove.size();
}

std::string Heap::debugState() {
	std::stringstream dbg;
	dbg << "--HEAP DATA--\n";
	dbg << "Num heap entries: ";
	dbg << heapMap_.size();
	dbg << "\n";

	for (auto iter = heapMap_.begin(); iter != heapMap_.end(); iter++) {
		dbg << "Entry: " << iter->first << " type "
				<< iter->second.type->typeName();

		if (iter->second.type->typeName().compare("string") == 0) {
			dbg << " string value: " << iter->second.pointer;
		}

		dbg << "\n";
	}

	dbg << "--END HEAP--\n";
	return dbg.str();
}

} /* namespace VM */

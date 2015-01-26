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

    /**
     * Returns true if the entry given is a valid reference to an entry on the heap
     */
    bool validReference(long entry);
    
    /**
     * Get the type 
     */
    SmartPointer<VMEntryType> getType(long entry);
    
    /**
     * Get a smartpointer to the allocation, this will lead to the data persisting after the heap is destroyed
     */
    SmartPointer<uint8_t> getSmartPointer(long entry);
    
    /**
     * Returns the address in memory of the heap entries data
     */
    uint8_t* getAddress(long entry);
    
    /**
     * Returns the size in bytes of a heap entry
     */
    int getSize(long entry);

    void flag(long i);
    void lock(long i);
    void unlock(long i);

    /**
     * This function deletes any unflagged heap elements and then sets flag states for the next garbage collector run
     */
    int processUnflagged();

    /**
     * Returns some debug information about the heap
     */
    std::string debugState();
};

} /* namespace VM */
#endif /* HEAP_HPP_ */

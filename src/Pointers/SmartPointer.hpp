#ifndef _SMART_POINTER_DEF_H_
#define _SMART_POINTER_DEF_H_
#include "ReferenceCounter.hpp"
#include <mutex>

template < typename T > class SmartPointer {
private:
	T* pointerData;
	ReferenceCounter* counter;
	std::mutex lock;

	void Release() {

		lock.lock();

		if (counter->Release() < 1) {
			delete pointerData;
			delete counter;

			pointerData = nullptr;
			counter = nullptr;
		}

		lock.unlock();

	}

public:

	SmartPointer() : pointerData(0), counter(0) {

		//Create a new counter for the pointer
		counter = new ReferenceCounter();

		//Increment the counter
		counter->Attach();
	}

	SmartPointer(T* value) : pointerData(value), counter(0) {
		counter = new ReferenceCounter();
		counter->Attach();
	}

	SmartPointer(SmartPointer<T> const& sp) : pointerData(sp.pointerData), counter(sp.counter) {
		counter->Attach();
	}

	~SmartPointer() {
		Release();
	}

	T& operator* () {
		return *pointerData;
	}

	T* operator-> () {
		return pointerData;
	}

	T* Get() {
		return pointerData;
	}

	inline bool Null() {

		if (pointerData == 0) {
			return true;
		}

		return false;
	}

	SmartPointer<T>& operator= (SmartPointer<T> const& rhs) {

		if (this != &rhs) {

			Release();

			pointerData = rhs.pointerData;
			counter = rhs.counter;
			counter->Attach();

		}

		return *this;
	}
};

#define SP SmartPointer
#endif //_SMART_POINTER_DEF_H_

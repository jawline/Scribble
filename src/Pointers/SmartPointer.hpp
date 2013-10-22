#ifndef _SMART_POINTER_DEF_H_
#define _SMART_POINTER_DEF_H_
#include "ReferenceCounter.hpp"
#include <mutex>
#include <memory>

/**
template<typename T> class SmartPointer {
private:
	T* data_;
	ReferenceCounter* counter_;

public:

	SmartPointer() :
			data_(nullptr), counter_(nullptr) {

		//Create a new counter for the pointer
		counter_ = new ReferenceCounter();

		//Increment the counter
		counter_->Attach();
	}

	SmartPointer(T* data) : data_(data), counter_(nullptr) {
		counter_ = new ReferenceCounter();
		counter_->Attach();
	}

	SmartPointer(SmartPointer<T> const& old) :
			data_(old.data_), counter_(old.counter_) {
		counter_->Attach();
	}

	~SmartPointer() {

		if (counter_->Release() <= 0) {

			if (data_ != nullptr) {
				delete data_;
			}

			delete counter_;
		}

	}

	T& operator*() {
		return *data_;
	}

	T* operator->() {
		return data_;
	}

	T* Get() {
		return data_;
	}

	inline bool Null() {

		if (data_ == nullptr) {
			return true;
		}

		return false;
	}

	SmartPointer<T>& operator=(SmartPointer<T> const& other) {

		if (this != &other) {

			if (counter_->Release() <= 0) {

				if (data_ != nullptr) {
					delete data_;
				}

				delete counter_;
			}

			data_ = other.data_;
			counter_ = other.counter_;
			counter_->Attach();
		}

		return *this;
	}
};*/

#define SmartPointer std::shared_ptr
#define SP SmartPointer
#endif //_SMART_POINTER_DEF_H_

#ifndef _VMSTACK_DEF_H_
#define _VMSTACK_DEF_H_
#include <stdio.h>
#include <string.h>
#include <exception>
#include <stdexcept>

namespace VM {

class StackEmptyException: public std::exception {
	virtual const char* what() const throw () {
		return "Pop called on empty stack";
	}

};

class VMStack {
private:
	uint8_t* data_;
	size_t current_;
	size_t max_;

	static const int cDefaultSize = 64;
	static const int cExpandChunkSize = 64;

	void expand() {

		uint8_t* newData = new uint8_t[max_ + cExpandChunkSize];

		for (unsigned int i = 0; i < max_; ++i) {
			newData[i] = data_[i];
		}

		delete[] data_;

		data_ = newData;
		max_ = max_ + cExpandChunkSize;
	}

public:

	VMStack() {

		data_ = new uint8_t[cDefaultSize];
		current_ = 0;
		max_ = cDefaultSize;
	}

	~VMStack() {

		if (data_ != nullptr) {
			delete[] data_;
			current_ = 0;
			max_ = 0;
		}

	}

	void pushByte(uint8_t a) {

		if (current_ >= max_) {
			expand();
		}

		data_[current_] = a;
		current_++;
	}

	uint8_t popByte() {

		if (current_ == 0) {
			throw StackEmptyException();
		}

		current_--;
		return data_[current_];
	}

	uint8_t getByte(unsigned int i) {
		return data_[i];
	}

	void pushLong(long i) {
		*((long*) (data_+current_)) = i;
		current_ += 8;
	}

	long popLong() {
		current_ -= 8;
		return *((long*)(data_+current_));
	}

	size_t size() {
		return current_;
	}

	void reset() {
		current_ = 0;
	}
};

}

#endif //_VMSTACK_DEF_H_

#ifndef _STACK_DEF_H_
#define _STACK_DEF_H_
#include <stdio.h>
#include <string.h>
#include <exception>
#include <stdexcept>

class StackEmptyException : public std::exception {
  virtual const char* what() const throw()
  {
    return "Pop called on empty stack";
  }

};

class Stack {
private:
	uint8_t* data_;
	size_t current_;
	size_t max_;

	static const int cDefaultSize = 1024;
	static const int cExpandChunkSize = 1024;


	void expand() {
		printf("Expanding stack from %i to %i entries\n", max_, max_ + cExpandChunkSize);

		uint8_t* newData = new uint8_t[max_ + cExpandChunkSize];
		memcpy(newData, data_,sizeof(uint8_t) * max_);
		delete[] data_;

		data_ = newData;
		max_ = max_ + cExpandChunkSize;
	}

public:

	Stack() {

		data_ = new uint8_t[cDefaultSize];
		current_ = 0;
		max_ = cDefaultSize;

		printf("Initialized new stack of size %i\n", cDefaultSize);

	}

	~Stack() {
		
		if (data_ != nullptr) {
			delete[] data_;
			current_ = 0;
			max_ = 0;
		}
	}

	void pushb(uint8_t a) {

		if (current_ >= max_) {
			expand();
		}

		data_[current_] = a;
		current_++;
	}

	uint8_t popb() {

		if (current_ == 0) {
			throw StackEmptyException();
		}

		current_--;
		return data_[current_];
	}

	size_t size() {
		return current_;
	}

	void reset() {
		current_ = 0;
	}
};

#endif //_STACK_DEF_H_
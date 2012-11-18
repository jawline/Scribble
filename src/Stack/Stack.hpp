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

template <class Type>
class Stack {
private:
	Type* data_;
	size_t current_;
	size_t max_;

	static const int cDefaultSize = 1024;
	static const int cExpandChunkSize = 1024;


	void expand() {
		printf("Expanding stack from %i to %i entries\n", max_, max_ + cExpandChunkSize);

		Type* newData = new Type[max_ + cExpandChunkSize];
		memcpy(newData, data_,sizeof(Type) * max_);
		delete[] data_;

		data_ = newData;
		max_ = max_ + cExpandChunkSize;
	}

public:

	Stack() {

		data_ = new Type[cDefaultSize];
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

	void push(Type a) {

		if (current_ >= max_) {
			expand();
		}

		data_[current_] = a;
		current_++;
	}

	Type pop() {

		if (current_ == 0) {
			throw StackEmptyException();
		}

		current_--;
		return data_[current_];
	}

	Type peek() {

		if (current_ == 0) {
			throw StackEmptyException();
		}

		return data_[current_ - 1];
	}

	size_t size() {
		return current_;
	}
};

#endif //_STACK_DEF_H_

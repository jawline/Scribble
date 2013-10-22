#ifndef _REFERENCE_COUNTER_DEF_H_
#define _REFERENCE_COUNTER_DEF_H_

class ReferenceCounter {
private:
	int count_;

public:

	ReferenceCounter() {
		count_ = 0;
	}

	void Attach() {
		count_++;
	}

	int Release() {
		return --count_;
	}

};

#endif //_REFERENCE_COUNTER_DEF_H_

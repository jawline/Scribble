#ifndef _REFERENCE_COUNTER_DEF_H_
#define _REFERENCE_COUNTER_DEF_H_

class ReferenceCounter {
private:
	int count;

public:

	void Attach() {
		count++;
	}

	int Release() {
		return --count;
	}

};

#endif //_REFERENCE_COUNTER_DEF_H_

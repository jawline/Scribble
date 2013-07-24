/*
 * VMEntryType.hpp
 *
 *  Created on: Jul 21, 2013
 *      Author: blake
 */

#ifndef VMENTRYTYPE_HPP_
#define VMENTRYTYPE_HPP_
#include <Pointers/SmartPointer.hpp>
#include <string>

namespace VM {

class VMEntryType {
private:

	std::string name_;
	bool reference_;
	bool array_;

	//TODO: Potentially make this a pointer or smart pointer to reduce on space used by types.
	SP<VMEntryType> subtype_;

public:
	VMEntryType(std::string name, bool reference);
	VMEntryType(std::string name, SP<VMEntryType> subtype);

	virtual ~VMEntryType();

	std::string typeName();
	bool isReference();

	bool isArray();
	SP<VMEntryType> arraySubtype();

	std::string debugType() {
		std::string res = "Name: " + name_ + " ";

		if (reference_) {
			res += "is a reference ";
		}

		if (array_) {
			res += "is an array ";
		}

		return res + "\n";
	}
};

} /* namespace VM */
#endif /* VMENTRYTYPE_HPP_ */

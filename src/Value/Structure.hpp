/*
 * Structure.hpp
 *
 *  Created on: 25 May 2013
 *      Author: blake
 */

#ifndef STRUCTURE_HPP_
#define STRUCTURE_HPP_
#include "Type.hpp"
#include "Value.hpp"
#include "StructureData.hpp"

class Structure: public Value {
private:
	Type* type_;
	SafeStructureData data_;

public:
	Structure(Type* type);
	virtual ~Structure();

	void applyOperator(ValueOperator, Value* other);
	Type* type();
	Value* clone();

	void setData(SafeStructureData data) {
		data_ = data;
	}

	SafeStructureData data() {
		return data_;
	}

};

#endif /* STRUCTURE_HPP_ */

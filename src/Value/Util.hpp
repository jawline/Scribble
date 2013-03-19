/*
 * Util.hpp
 *
 *  Created on: 19 Mar 2013
 *      Author: blake
 */

#ifndef UTIL_HPP_
#define UTIL_HPP_
#include "Value.hpp"

class ValueUtil {
private:
	ValueUtil();
	virtual ~ValueUtil();

public:

	static Value* generateValue(ValueType type);

};

#endif /* UTIL_HPP_ */

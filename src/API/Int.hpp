/*
 * Int.hpp
 *
 *  Created on: 17 Nov 2013
 *      Author: blake
 */

#ifndef INT_HPP_
#define INT_HPP_
#include "Function.hpp"

namespace API {

class IntFromFloat32 : public Function  {
public:
	IntFromFloat32(std::string ns);
	virtual ~IntFromFloat32();

	API::APIValue execute(API::APIValue* values,
			VM::VirtualMachine* virt);

	virtual ScribbleCore::Type* getType();
	virtual const unsigned int numArgs();
	virtual ScribbleCore::Type* argType(unsigned int arg);
};

} /* namespace API */
#endif /* INT_HPP_ */

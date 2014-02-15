/*
 * Concat.hpp
 *
 *  Created on: 20 Sep 2013
 *      Author: blake
 */

#ifndef CONCAT_HPP_
#define CONCAT_HPP_
#include "Function.hpp"

namespace API {

class Concat : public Function {
public:
	Concat(std::string ns);
	virtual ~Concat();

	API::APIValue execute(API::APIValue* values,
			VM::VirtualMachine* virt);

	virtual ScribbleCore::Type* getType();
	virtual const unsigned int numArgs();
	virtual ScribbleCore::Type* argType(unsigned int arg);
};

} /* namespace API */
#endif /* CONCAT_HPP_ */

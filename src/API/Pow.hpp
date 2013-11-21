/*
 * Pow.hpp
 *
 *  Created on: 21 Nov 2013
 *      Author: blake
 */

#ifndef POW_HPP_
#define POW_HPP_
#include "Function.hpp"

namespace API {

class Pow: public Function {
private:
	std::string namespace_;

public:
	Pow(std::string ns);
	virtual ~Pow();

	/**
	 * Execute the function and return the result value.
	 */

	virtual Value* execute(std::vector<Value*> arguments);

	/**
	 * Returns the resulting modulo as an API value.
	 */

	virtual APIValue execute(API::APIValue* values, VM::VirtualMachine* virt);

	/**
	 * Get the return type of the function.
	 */

	virtual Type* getType();

	/**
	 * Get the number of arguments (2)
	 */

	virtual const unsigned int numArgs();

	/**
	 * Get the arg type for a given argument ( Both Integer)
	 */

	virtual Type* argType(unsigned int arg);
};

class PowFloat32: public Function {
private:
	std::string namespace_;

public:
	PowFloat32(std::string ns);
	virtual ~PowFloat32();

	/**
	 * Execute the function and return the result value.
	 */

	virtual Value* execute(std::vector<Value*> arguments);

	/**
	 * Returns the resulting modulo as an API value.
	 */

	virtual APIValue execute(API::APIValue* values, VM::VirtualMachine* virt);

	/**
	 * Get the return type of the function.
	 */

	virtual Type* getType();

	/**
	 * Get the number of arguments (2)
	 */

	virtual const unsigned int numArgs();

	/**
	 * Get the arg type for a given argument ( Both Integer)
	 */

	virtual Type* argType(unsigned int arg);
};

} /* namespace API */
#endif /* POW_HPP_ */

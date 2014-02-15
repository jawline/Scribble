/*
 * APIFunction.hpp
 *
 *  Created on: 6 Jan 2014
 *      Author: blake
 */

#ifndef APIFUNCTION_HPP_
#define APIFUNCTION_HPP_
#include <vector>
#include <API/Function.hpp>
#include <API/Value/APIValue.hpp>
#include <Scribble/Value/Type.hpp>

namespace API {

class APIFunction : public Function {
private:
	ScribbleCore::Type* returnType_;
	std::vector<ScribbleCore::Type*> types_;
	API::APIValue (*fn_)(API::APIValue*, VM::VirtualMachine* virt);

public:

	APIFunction(std::string name, std::string package, ScribbleCore::Type* returnType, std::vector<ScribbleCore::Type*> types,
			API::APIValue (*fn)(API::APIValue*, VM::VirtualMachine* virt));

	virtual ~APIFunction();

	ScribbleCore::Type* getType() {
		return returnType_;
	}

	const unsigned int numArgs() {
		return types_.size();
	}

	ScribbleCore::Type* argType(unsigned int arg) {
		return types_[arg];
	}

	APIValue execute(API::APIValue* values, VM::VirtualMachine* virt) {
		return fn_(values, virt);
	}

};

} /* namespace API */
#endif /* APIFUNCTION_HPP_ */

#ifndef _FUNCTION_H_
#define _FUNCTION_H_
#include <Pointers/SmartPointer.hpp>
#include <vector>
#include <VM/Constants.hpp>
#include <VM/VMFunc.hpp>
#include <VM/VirtualMachine.hpp>
#include <API/Value/APIValue.hpp>
#include <sstream>
#include <Scribble/Function/FunctionSignature.hpp>

namespace API {

/**
 * Virtual Function class implemented to create Scribble functions.
 * @author Blake Loring
 */

class Function {
private:
	std::string name_;
	std::string namespace_;

protected:
	ScribbleCore::FunctionSignature signature_;

	void setSignature(ScribbleCore::FunctionSignature sig) {
		signature_ = sig;
	}

public:

	Function(std::string name, std::string ns) :
			name_(name), namespace_(ns) {

	}

	virtual ~Function() {
	}

	/**
	 * This function executes the given API::Function and returns it's result. It called by the more complex execute(VM::VirtualMachine*) after that function has converted all arguments into API values.
	 * @param args The arguments passed to the function
	 * @param virt The virtual machine this function is being run in the context of.
	 * @return The resulting API value
	 */

	virtual APIValue execute(API::APIValue* values, VM::VirtualMachine* virt) {
		return API::APIValue();
	}

	virtual void execute(VM::VirtualMachine* virt) {

		APIValue* vals = new APIValue[numArgs()];

		for (int i = numArgs() - 1; i > -1; --i) {

			int64_t val;
			bool ref;

			virt->popStackLong(val, ref);

			if (ref) {
				vals[i] = API::APIValue(argType(i), virt->getHeap().getType(val),
						virt->getHeap().getSmartPointer(val), val);
			} else {
				vals[i] = API::APIValue(argType(i), val);
			}

		}

		APIValue returnVal = execute(vals, virt);

		if (returnVal.isReference()) {
			virt->setRegister(VM::vmReturnResultRegister, returnVal.getValue32(),
					true);
			virt->hitGc();
		} else {
			virt->setRegister(VM::vmReturnResultRegister, returnVal.getValue32(),
					false);
		}
	}

	/**
	 * Get the return type of the function
	 */

	virtual ScribbleCore::Type* getType() = 0;

	/**
	 * Return the number of arguments the function takes
	 */

	virtual const unsigned int numArgs() = 0;

	/**
	 * Get the expected type of the specified argument
	 */

	virtual ScribbleCore::Type* argType(unsigned int arg) = 0;

	virtual int debugCode(std::stringstream& gen) {
		gen << std::string("#NativeFunction");
		return 0;
	}

	virtual std::string getNamespace() {
		return namespace_;
	}

	virtual std::string getName() {
		return name_;
	}

	/**
	 * Returns true if this is a function written in Native code.
	 */

	virtual bool isNativeFunction() {
		return true;
	}

	/**
	 * If the function is scripted and not native this will generate a VMFunc for it.
	 */

	virtual SmartPointer<VM::VMFunc> generateScriptedFunc() {
		return SmartPointer<VM::VMFunc>(nullptr);
	}

	static SmartPointer<VM::VMFunc> getNativeFunction(SmartPointer<Function> func) {

		if (func->isNativeFunction()) {
			return SmartPointer<VM::VMFunc>(new VM::VMFunc(func->getName(), func));
		}

		return func->generateScriptedFunc();
	}

};

typedef SmartPointer<Function> SafeFunction;

}

#endif //_FUNCTION_H_

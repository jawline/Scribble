#ifndef _FUNCTION_H_
#define _FUNCTION_H_
#include <Pointers/SmartPointer.hpp>
#include <Scribble/Value/Value.hpp>
#include <vector>
#include <VM/VMFunc.hpp>
#include <VM/VirtualMachine.hpp>
#include <API/Value/APIValue.hpp>

namespace API {

/**
 * Virtual Function class implemented to create Scribble functions.
 * @author Blake Loring
 */

class Function {
private:
	std::string name_;
	std::string namespace_;

public:

	Function(std::string name, std::string ns) :
			name_(name), namespace_(ns) {

	}

	virtual ~Function() {
	}

	/**
	 * Execute the function and return the result value.
	 */

	virtual Value* execute(std::vector<Value*> arguments) = 0;
	virtual void execute(API::APIValue* values, VM::VirtualMachine* virt) {}
	virtual void execute(VM::VirtualMachine* virt) {

		APIValue* vals = new APIValue[numArgs()];

		for (int i = numArgs() - 1; i > -1; --i) {

			long val;
			bool ref;

			virt->popStackLong(val, ref);

			if (ref) {
				vals[i] = API::APIValue(virt->getHeap().getType(val),
						virt->getHeap().getAddress(val), val);
			} else {
				vals[i] = API::APIValue(val);
			}

		}

		execute(vals, virt);
	}

	/**
	 * Get the return type of the function.
	 */
	virtual Type* getType() = 0;
	virtual const unsigned int numArgs() = 0;
	virtual Type* argType(unsigned int arg) = 0;

	virtual int debugCode(std::stringstream& gen) {
		return 0;
	}

	virtual std::string getNamespace() {
		return namespace_;
	}

	virtual std::string getName() {
		return name_;
	}

	/**
	 * Function returns a valid VM::VMFunc of this function ( the object is registerable inside the VM )
	 * By default returns a native VM func to this function. Overload if custom VMFunc is required ( Such as ScriptedFunction )
	 */

	virtual VM::VMFunc generateVMFunction() {
		return VM::VMFunc(getName(), this);
	}

};

typedef SmartPointer<Function> SafeFunction;

}

#endif //_FUNCTION_H_

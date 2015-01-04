/*
 * Function.cpp
 *
 *  Created on: 7 Sep 2014
 *      Author: blake
 */

#include "Function.hpp"

namespace API {

void Function::setSignature(ScribbleCore::FunctionSignature sig) {

    signature_ = sig;
}

void Function::execute(VM::VirtualMachine* virt) {

    APIValue* vals = new APIValue[getSignature().getArguments().size()];

    for (int i = getSignature().getArguments().size() - 1; i > -1; --i) {

        int64_t val;
        bool ref;

        virt->popStackLong(val, ref);

        if (ref) {
            vals[i] = API::APIValue(getSignature().getArguments()[i]->type(),
                                    virt->getHeap().getType(val),
                                    virt->getHeap().getSmartPointer(val), val);
        } else {
            vals[i] = API::APIValue(getSignature().getArguments()[i]->type(),
                                    val);
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

int Function::debugCode(std::stringstream& gen) {

    if (isNativeFunction()) {
        gen << "#NativeFunction";
    } else {
        //Should always be overridden
        gen << "#NonNativeFunction";
    }

    return 0;
}

std::vector<SafeFunction> makeFunctionList(SafeFunction function) {
	std::vector<SafeFunction> list;
	list.push_back(function);
	return list;
}

}

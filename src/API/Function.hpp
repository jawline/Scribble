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
#include <Scribble/Value/Type.hpp>

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
    void setSignature(ScribbleCore::FunctionSignature sig);

  public:

    Function(std::string name, std::string ns) :
        name_(name), namespace_(ns), signature_(
            std::vector<ScribbleCore::TypeReference>(),
            ScribbleCore::makeTypeReference(
                ScribbleCore::getTypeManager().getType(
                    ScribbleCore::TypeUnresolved))) {

    }

    virtual ~Function() {
    }

    /**
     * This function executes the given API::Function and returns it's result. It called by the more complex execute(VM::VirtualMachine*) after that function has converted all arguments into API values.
     * @param args The arguments passed to the function
     * @param virt The virtual machine this function is being run in the context of.
     * @return The resulting API value
     */
    virtual APIValue execute(API::APIValue* values,
                             VM::VirtualMachine* virt) = 0;

    virtual void execute(VM::VirtualMachine* virt);

    virtual int debugCode(std::stringstream& gen);

    virtual std::string getNamespace() const {
        return namespace_;
    }

    virtual std::string getName() const {
        return name_;
    }

    /**
     * Returns true if this is a function written in Native code.
     */

    virtual bool isNativeFunction() const {
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

    ScribbleCore::FunctionSignature getSignature() const {
        return signature_;
    }

};

typedef SmartPointer<Function> SafeFunction;

}

#endif //_FUNCTION_H_

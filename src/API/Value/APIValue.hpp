/*
 * APIValue.hpp
 *
 *  Created on: 10 Sep 2013
 *      Author: blake
 */

#ifndef APIVALUE_HPP_
#define APIVALUE_HPP_

/**
 * Defines int32_t, int64_t and float32_t
 */

#include <types.h>

#include <VM/VMEntryType.hpp>
#include <VM/Constants.hpp>

#include <VM/VirtualMachine.hpp>
#include <Pointers/SmartPointer.hpp>
#include <Scribble/Function/FunctionSignature.hpp>
#include <Scribble/Value/Type.hpp>
#include <Scribble/Value/StructureInfo.hpp>
#include <Scribble/Value/TypeManager.hpp>

namespace API {

/**
 * The APIValue class contains the arguments for or return value from a
 * virtual machine function.
 *
 * It is a wrapper around the register value and heap data to provide an
 * easy way to extra useful data from the result of a VM execution or pass
 * information to it.
 */

class APIValue {
  private:
    ScribbleCore::Type* cType_;
    SmartPointer<VM::VMEntryType> vType_;
    SmartPointer<uint8_t> data_;
    int64_t val_;

  public:
    APIValue() {
        cType_ = ScribbleCore::getVoidType();
        val_ = 0;
        vType_ = nullptr;
        data_ = nullptr;
    }
    APIValue(ScribbleCore::Type* type, int64_t val);
    APIValue(ScribbleCore::Type* type, SmartPointer<VM::VMEntryType> vmType, SmartPointer<uint8_t> data, int64_t val);
    virtual ~APIValue();

    /**
     * This returns the value as a 64 bit signed integer.
     */

    int64_t getValue64() {
        return val_;
    }

    /**
     * This returns the value as a 32 bit signed integer.
     */

    int32_t getValue32() {
        return val_;
    }

    /**
     * This returns the value as a 32 bit floating point number.
     */

    float32_t getValueFloat32() {
        return *((float32_t*) &val_);
    }

    /**
     * If the value is a string, return a pointer to the string.
     */

    char* getValueString() {
        return (char*) getReferencePointer();
    }

    /**
     * Returns true if the value is equal to VM::vmTrue ( The VMs representation of a true boolean ) otherwise returns false.
     */

    bool getValueBoolean() {

        if (val_ != VM::vmFalse) {
            return true;
        }

        return false;
    }

    /**
     * If the value is a reference then return its type.
     */
    SmartPointer<VM::VMEntryType> getReferenceType() const;

    /**
     * For a reference this will return a pointer to the reference data, for primitive types this will return a null pointer.
     */
    uint8_t* getReferencePointer() const;

    /**
     * Returns a pointer to the type of this API::APIValue
     */
    ScribbleCore::Type* getType() const;

    /**
     * Returns true if this APIValue is a reference to a piece of data on the heap.
     */
    bool isReference() const;

    /**
     * Returns true if the register value is set to zero.
     */
    bool isNull() const;

    /**
     * Will return the value of a field within the structure pointer to by a reference
     * if that field exists. If the reference is not a structure or the field does not
     * exist then APIValue(0) will be returned.
     */
    APIValue getField(std::string const& name, VM::VirtualMachine* vm) const;

    /**
     * Return the length of the array pointer to by a reference.
     *
     * If the APIvalue is not an array reference or the reference is a null
     * reference then 0 will be returned.
     */
    unsigned int getArrayLength(VM::VirtualMachine* vm) const;

    APIValue getIndex(unsigned int index, VM::VirtualMachine* vm);

    void setField(std::string const& name, API::APIValue val, VM::VirtualMachine* vm);

    void setIndex(unsigned int index, API::APIValue val, VM::VirtualMachine* vm);

    /**
     * Pushes this APIValue to the virtual machine stack and marks it as a
     * reference if it resides on the heap.
     */
    void pushToVM(VM::VirtualMachine* virt);

    static API::APIValue makeBoolean(bool val);
    static API::APIValue makeInt32(int val);
    static API::APIValue makeFloat32(float32_t val);
    static API::APIValue makeString(std::string const& text, VM::VirtualMachine* vm);
};

} /* namespace API */
#endif /* APIVALUE_HPP_ */

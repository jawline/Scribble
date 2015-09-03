/*
 * VirtualMachine.cpp
 *
 *  Created on: 28 May 2013
 *      Author: blake
 */

#include "VirtualMachine.hpp"
#include "OpCodes.hpp"
#include "JumpTypes.hpp"
#include "Constants.hpp"
#include "VirtualMachine_Debug.hpp"
#include <API/Function.hpp>
#include <stdio.h>

namespace VM {

VirtualMachine::VirtualMachine() :
    currentInstruction(0), stackBasePointer(0), stackCurrentPointer(0) {

    //Allocate memory for registers
    registers_ = new int64_t[vmNumRegisters];
    registerReference_ = new bool[vmNumRegisters];

    //Initialize all the registers
    for (unsigned int i = 0; i < vmNumRegisters; ++i) {
        registers_[i] = 0;
        registerReference_[i] = false;
    }

    auto charType = SmartPointer<VMEntryType>(new VMEntryType("char", 1, false));

    //Register all the primitive types
    registerEntry("char", charType);
    registerEntry("bool", NamespaceEntry(SmartPointer<VMEntryType>(new VMEntryType("bool", 1, false))));
    registerEntry("short", NamespaceEntry(SmartPointer<VMEntryType>(new VMEntryType("short", 2, false))));
    registerEntry("int", NamespaceEntry(SmartPointer<VMEntryType>(new VMEntryType("int", 4, false))));
    registerEntry("float32", NamespaceEntry(SmartPointer<VMEntryType>(new VMEntryType("float32", 4, false))));

    registerEntry("long", NamespaceEntry(SmartPointer<VMEntryType>(new VMEntryType("int", 8, false))));
    registerEntry("__fnptr",NamespaceEntry(SmartPointer<VMEntryType>(new VMEntryType("__fnptr", charType))));
    registerEntry("string", NamespaceEntry(SmartPointer<VMEntryType>(new VMEntryType("string", charType))));

    stack_ = new uint8_t[vmStackIncrease];
    currentStackHeight_ = vmStackIncrease;
    gcStat_ = 0;
}

VirtualMachine::~VirtualMachine() {
}

SmartPointer<VMEntryType> VirtualMachine::findType(std::string const& name) {

    NamespaceEntry entry;

    //If the namespace entry is not found in the namespace
    if (!VM::NamespaceEntry::searchNamespace(namespace_, name, entry)) {

        VM_PRINTF_LOG("Type %s not found, inspecting to check if array\n", name.c_str());

        //If it starts with 'array(' try to generate it from existing types
        char const* prefix = "array(";

        if (strncmp(prefix, name.c_str(), strlen(prefix)) == 0) {

            std::string subtypeName = name.substr(strlen(prefix), name.size() - strlen(prefix) - 1);

            VM_PRINTF_LOG("Generating subtype %s\n", subtypeName.c_str());

            SmartPointer<VMEntryType> subtype = findType(subtypeName);

            if (subtype.get() == nullptr) {
                VM_PRINTF_FATAL("Cannot create array of invalid subtype %s\n", subtypeName.c_str());
                return nullptr;
            }

            SmartPointer<VMEntryType> entryType = SmartPointer<VMEntryType>(new VMEntryType(name, subtype));
            registerEntry(name, entryType);
            VM_PRINTF_LOG("Generating new type %s\n", name.c_str());
            return entryType;
        } else {
            VM_PRINTF_LOG("Prefix of %s does not match with array(\n", name.c_str());
            return nullptr;
        }
    }

    //If the entry in the namespace specified is not a type then return null
    if (entry.getType() != Type) {
        VM_PRINTF_LOG("Error searched type %s (%i)\n", name.c_str(), entry.getType());
        return nullptr;
    }

    return entry.getTypeReference();
}

void VirtualMachine::getRegister(uint8_t reg, int64_t& val, bool& isReg) {
    val = registers_[reg];
    isReg = registerReference_[reg];
}

void VirtualMachine::setRegister(uint8_t reg, int64_t val, bool ref) {
    registers_[reg] = val;
    registerReference_[reg] = ref;
}

bool VirtualMachine::returnToPreviousFunction(
    SmartPointer<VMFunc>& currentFunction, InstructionSet& set) {

    if (currentVmState_.size() > 0) {

        VMState top = currentVmState_.top();
        currentVmState_.pop();

        currentFunction = top.func_;
        set = currentFunction->getInstructions();
        currentInstruction = top.pc_;

        return true;
    } else {
        return false;
    }
}

void VirtualMachine::execute(std::string function) {

    NamespaceEntry functionEntry;

    if (!VM::NamespaceEntry::searchNamespace(namespace_, function,
            functionEntry) || functionEntry.getType() != Function) {
        VM_PRINTF_FATAL("%s is not a registered function\n", function.c_str());
    }

    currentFunction = functionEntry.getFunction();

    if (currentFunction->isNative()) {
        currentFunction->getFunction()->execute(this);
        return;
    }

    InstructionSet instructionSet = currentFunction->getInstructions();

    currentInstruction = instructionSet.getStartLocation();

    shouldReturn = false;

    while (!shouldReturn) {

        //If the current PC is above the number of instructions in this function then attempt to return. Else execute the instruction at the PC.
        if (currentInstruction >= instructionSet.getSizeInBytes()) {

            if (!returnToPreviousFunction(currentFunction, instructionSet)) {
                shouldReturn = true;
            }

        } else {

            switch (instructionSet.getByte(currentInstruction)) {

            /**
             *  Loads the constant data at the specified constant index into the given register.
             *  Capable of loading elements into the heap and assigning their reference if their initial data is already known ( Such as pushing strings ).
             */

            case OpLoadConstant: {
                opLoadConstant(instructionSet);
                break;
            }

            /**
             * Copy whatever is in the target register into the destination register copying over whether it is a reference or not.
             */

            case OpMove: {
                opMove(instructionSet);
                break;
            }

            /**
             * Jump to a different instruction
             */

            case OpJump: {
                opJump(instructionSet);
                break;
            }

            /**
             * Add the left and right registers and place the result in the dest register.
             */

            case OpAdd: {
                opAdd(instructionSet);
                break;
            }

            /**
             * Subtract the left and right registers and place the result in the dest register.
             */

            case OpSub: {
                opSub(instructionSet);
                break;
            }

            /**
             * Multiply the left and right registers and place the result in the dest register.
             */

            case OpMul: {
                opMul(instructionSet);
                break;
            }

            /**
             * Divide the left and right registers and place the result in the dest register.
             */

            case OpDiv: {
                opDiv(instructionSet);
                break;
            }

            case OpInc: {
                opInc(instructionSet);
                break;
            }

            case OpDec: {
                opDec(instructionSet);
                break;
            }

            case OpNot: {
                opNot(instructionSet);
                break;
            }

            case OpAddFloat32: {
                opAddFloat32(instructionSet);
                break;
            }

            case OpSubFloat32: {
                opSubFloat32(instructionSet);
                break;
            }

            case OpMulFloat32: {
                opMulFloat32(instructionSet);
                break;
            }

            case OpDivFloat32: {
                opDivFloat32(instructionSet);
                break;
            }

            case OpCmpFloat32: {
                opCmpFloat32(instructionSet);
                break;
            }

            /**
             * Test if two registers are equal. If true then execute the next instruction else skip it.
             */

            case OpEqual: {
                opEqual(instructionSet);
                break;
            }

            case OpNotEqual: {
                opNotEqual(instructionSet);
                break;
            }

            case OpEqualZero: {
                opEqualZero(instructionSet);
                break;
            }

            /**
             *  Test if one register is less than another. If true execute next instruction otherwise skip it.
             */

            case OpLessThan: {
                opLessThan(instructionSet);
                break;
            }

            case OpGreaterThan: {
                opGreaterThan(instructionSet);
                break;
            }

            case OpGreaterThanOrEqual: {
                opGreaterThanOrEqual(instructionSet);
                break;
            }

            /**
             * OpPushRegisters
             * Push registers, starting from the start register and pushing numregisters sequentially from it
             * StartRegister - Offset 1 - 1 byte
             * NumRegisters - Offset 2 - 1 byte
             */
            case OpPushRegisters: {
                opPushRegisters(instructionSet);
                break;
            }

            /**
             * Pop n registers starting from the start+nth register and the last pop acting on the start register
             */
            case OpPopRegisters: {
                opPopRegisters(instructionSet);
                break;
            }

            /**
             * Pop a long from the stack and ignore it ( Don't put it in any registers ).
             */

            case OpPopNil: {
                opPopNil(instructionSet);
                break;
            }

            /**
             * Test whether the register left's value is <= than the register right.
             * If true execute the next instruction
             * Else skip the next function.
             */

            case OpLessThanOrEqual: {
                opLessThanOrEqual(instructionSet);
                break;
            }

            case OpStructGetField: {
                opStructGetField(instructionSet);
                break;
            }

            case OpStructSetField: {
                opStructSetField(instructionSet);
                break;
            }

            /**
             * Set the specified element in the target array to the given data value.
             */

            case OpArraySet: {
                opArraySet(instructionSet);
                break;
            }

            /**
             * Set the dataRegisters value to be the value of the array at the specified index.
             */

            case OpArrayGet: {
                opArrayGet(instructionSet);
                break;
            }

            case OpNewStruct: {
                opNewStruct(instructionSet);
                break;
            }

            /**
             * Create a new array of the specified type ( Stored in constants ) and length ( The value of lengthRegister ) and set its reference to the specified register.
             */

            case OpNewArray: {
                opNewArray(instructionSet);
                break;
            }

            /**
             * Set the value of dest register to be the length of the array pointed to by the value of the array length register.
             */

            case OpArrayLength: {
                opArrayLength(instructionSet);
                break;
            }

            /**
             * Call the specified function. Two modes Constant or Heap. If Constant mode name of function is stored in constant instruction set zone otherwise name of function is pointed to by string in heap specified by register.
             */

            case OpCallFn: {
                opCallFn(instructionSet);
                break;
            }

            /**
             * Return to the previous function that was running or exit.
             */

            case OpReturn: {
                opReturn(instructionSet);
                break;
            }

            default: {
                VM_PRINTF_FATAL("Invalid instruction %li. %ii\n",
                                currentInstruction, instructionSet.getByte(currentInstruction));
                return;
            }

            }

            //After each instruction check the gcStat and
            //if it has hit the hit limit then run the garbage collector.

            if (gcStat_ > GarbageCollectHitLimit) {
                garbageCollection();
                gcStat_ = 0;
            }

        }

    }

    //As the function exits run the garbage collector and reset the GC stat value
    garbageCollection();
    gcStat_ = 0;

}

void VirtualMachine::pushRegister(uint8_t reg) {

    if (registerReference_[reg]) {
        markStackReference();
    }

    pushStackLong(registers_[reg]);
}

void VirtualMachine::garbageCollection() {

    VM_PRINTF_WARN("%s\n", "TODO: GC CHECK STACK");
    VM_PRINTF_WARN("%s\n", "TODO: GC CHECK HEAP");

    VM_PRINTF_LOG("%s\n", "Garbage collector running");

    std::vector<long> toInvestigate;
    toInvestigate.clear();

    //Loop through all registers flagging any references found and adding them to a list of references to explore
    for (unsigned int i = 0; i < vmNumRegisters; ++i) {

        if (registerReference_[i] && heap_.validReference(registers_[i])) {
            heap_.flag(registers_[i]);
            toInvestigate.push_back(registers_[i]);
        }

    }

    //Flag every reference on the stack and add it to the list of objects to investigate.
    for (unsigned int i = 0; i < stackReferences_.size(); i++) {
        heap_.flag(stackLong(stackReferences_[i]));
        toInvestigate.push_back(stackLong(stackReferences_[i]));
    }

    //Investigate every flagged object. Flagging anything that they may reference
    for (unsigned int i = 0; i < toInvestigate.size(); ++i) {

        long next = toInvestigate[i];

        if (!heap_.validReference(next)) {
            VM_PRINTF_FATAL("ERROR: Reference at register %i is not valid\n",
                            i);
        }

        SmartPointer<VMEntryType> nextType = heap_.getType(next);

        if (nextType.get() == nullptr) {
            VM_PRINTF_FATAL("%s", "ERROR: Heap type failure\n");
        }

        //If it is an array check if it is an array of references and if it is flag and check every reference.
        if (nextType->getBaseType() == VM::VMArray) {

            SmartPointer<VMEntryType> subtype = nextType->arraySubtype();

            if (subtype->isReference()) {

                uint8_t* dataOriginal = heap_.getAddress(next);
                long* data = (long*) dataOriginal;

                //Loop a pointer between the start and end of the data
                while (((uint8_t*) data) < (dataOriginal + heap_.getSize(next))) {

                    //Don't flag nullptrs
                    if (*data != 0) {
                        heap_.flag(*data);
                        toInvestigate.push_back(*data);
                    }

                    data++;
                }

            }

        } else if (nextType->getBaseType() == VMStructure) {

            //For every field in the structure
            for (unsigned int i = 0; i < nextType->getStructureFields().size(); i++) {

                //If that field is a reference to anything on the heap
                if (nextType->getStructureFields()[i]->getType()->isReference()) {

                    //Get a pointer to the structure data
                    uint8_t* structurePtr = heap_.getAddress(next);

                    //Get a pointer to the reference within the structure
                    long* referencePtr = (long*) (structurePtr + nextType->getStructureFieldOffset(i));

                    //If we aren't looking at a null pointer
                    if (*referencePtr != 0) {
                        heap_.flag(*referencePtr);
                        toInvestigate.push_back(*referencePtr);
                    }

                }

            }

        } else if (nextType->isReference()) {
            long ref = *(long*) (heap_.getAddress(next));
            heap_.flag(ref);
            toInvestigate.push_back(ref);
        }

    }

    //After everything delete what remains
    int numDeleted = heap_.processUnflagged();

    VM_PRINTF_LOG("Garbage collector done deleting %i elements\n", numDeleted);
}

void VirtualMachine::printState() {

    VM_PRINTF_LOG("%s", "--VM STATE--\n");

    for (unsigned int i = 0; i < stackCurrentPointer; i++) {
        VM_PRINTF_LOG("%x ", stack_[i]);
    }

    VM_PRINTF_LOG("%s", "\n");

    for (unsigned int i = 0; i < vmNumRegisters; i += 3) {

        if (i < vmNumRegisters) {
            VM_PRINTF_LOG("#%i:%li ", i, (long int )registers_[i]);
        }

        if (i + 1 < vmNumRegisters) {
            VM_PRINTF_LOG("#%i:%li ", i + 1, (long int )registers_[i + 1]);
        }

        if (i + 2 < vmNumRegisters) {
            VM_PRINTF_LOG("#%i:%li", i + 2, (long int )registers_[i + 2]);
        }

        VM_PRINTF_LOG("%s", "\n");
    }

    VM_PRINTF_LOG("%s\n", heap_.debugState().c_str());

    VM_PRINTF_LOG("%s", "--VM STATE END--\n");
}

void VirtualMachine::logMessage(VMLogLevel level, std::string message) {
    switch (level) {

    case Log: {
        VM_PRINTF_LOG("%s", message.c_str());
        break;
    }

    case Debug: {
        VM_PRINTF_DBG("%s", message.c_str());
        break;
    }

    case Warn: {
        VM_PRINTF_WARN("%s", message.c_str());
        break;
    }

    case Fatal: {
        VM_PRINTF_FATAL("%s", message.c_str());
        break;
    }

    }
}

} /* namespace VM */

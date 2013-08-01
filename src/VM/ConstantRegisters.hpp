#ifndef _CONSTANT_REGISTERS_DEF_H_
#define _CONSTANT_REGISTERS_DEF_H_

namespace VM {

const static unsigned int vmNumRegisters = 32;
const static unsigned int vmNumReservedRegisters = 6;
const static unsigned int vmProgramCounter = 0;
const static unsigned int vmStackBasePointer = 1;
const static unsigned int vmStackCurrentPointer = 2;
const static unsigned int vmTempRegisterOne = 3;
const static unsigned int vmTempRegisterTwo = 4;
const static unsigned int vmTempRegisterThree = 5;

}

#endif //_CONSTANT_REGISTERS_DEF_H_

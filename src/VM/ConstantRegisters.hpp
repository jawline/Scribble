#ifndef _CONSTANT_REGISTERS_DEF_H_
#define _CONSTANT_REGISTERS_DEF_H_

namespace VM {

const static unsigned int vmNumRegisters = 32;
const static unsigned int vmNumReservedRegisters = 3;
const static unsigned int vmTempRegisterOne = 0;
const static unsigned int vmTempRegisterTwo = 1;
const static unsigned int vmTempRegisterThree = 2;
const static unsigned int vmReturnResultRegister = vmTempRegisterThree;

}

#endif //_CONSTANT_REGISTERS_DEF_H_

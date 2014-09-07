#ifndef _CONSTANT_REGISTERS_DEF_H_
#define _CONSTANT_REGISTERS_DEF_H_

namespace VM {

const static int vmNumRegisters = 32;
const static int vmNumReservedRegisters = 3;
const static int vmTempRegisterOne = 0;
const static int vmTempRegisterTwo = 1;
const static int vmTempRegisterThree = 2;
const static int vmReturnResultRegister = vmTempRegisterThree;

}

#endif //_CONSTANT_REGISTERS_DEF_H_

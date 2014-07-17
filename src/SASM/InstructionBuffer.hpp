#ifndef _INSTRUCTION_BUFFER_DEF_H_
#define _INSTRUCTION_BUFFER_DEF_H_
#include <iostream>
#include <string>
#include <types.h>
#include <string.h>
#include <VM/OpCodes.hpp>
#include <VM/Constants.hpp>
#include <VM/ConstantTypes.hpp>
#include <VM/JumpTypes.hpp>

void InitInstructionBuffer();
void DeleteInstructionBuffer();

uint8_t* getInstructionBuffer();
int getInstructionBufferSize();

uint8_t* getInstructionConstant();
int getInstructionConstantSize();

void LoadInt(int val, uint8_t dest);
void LoadFloat32(float32_t val, uint8_t dest);
void PopNil();
void ArrayLength(uint8_t reg, uint8_t dst);
void LoadLong(long val, uint8_t reg);
void CallFunction(char const* name);
void CallFunctionFromRegister(uint8_t reg);
void Return();
void PushRegisters(uint8_t start, uint8_t num);
void PopRegisters(uint8_t start, uint8_t num);
void ArraySet(uint8_t dataReg, uint8_t arrayReg, uint8_t indexReg);
void ArrayGet(uint8_t arrayReg, uint8_t indexReg, uint8_t dataReg);
void Structure(std::string type, uint8_t dst);
void StructureFieldSet(uint8_t tgtArray, uint8_t index, uint8_t data);
void StructureFieldGet(uint8_t tgtArray, uint8_t index, uint8_t data);
void Array(std::string type, uint8_t sizereg, uint8_t reg);
void LoadString(char const* str, uint8_t reg);
void LoadFunctionReference(char const* str, uint8_t reg);
void Add(uint8_t left, uint8_t right, uint8_t dest);
void Subtract(uint8_t left, uint8_t right, uint8_t dest);
void Multiply(uint8_t left, uint8_t right, uint8_t dest);
void Divide(uint8_t left, uint8_t right, uint8_t dest);
void AddFloat32(uint8_t left, uint8_t right, uint8_t dest);
void SubtractFloat32(uint8_t left, uint8_t right, uint8_t dest);
void MultiplyFloat32(uint8_t left, uint8_t right, uint8_t dest);
void DivideFloat32(uint8_t left, uint8_t right, uint8_t dest);
void CompareFloat32(uint8_t left, uint8_t right, uint8_t dest);
void Move(uint8_t target, uint8_t dest);
void JumpDirect(int inst);
void JumpDirectRelative(int inst);
void JumpRegister(int reg);
void JumpRegisterRelative(int reg);
void TestEqual(uint8_t left, uint8_t right);
void LessThan(uint8_t left, uint8_t right);
void GreaterThan(uint8_t left, uint8_t right);
void LessThanOrEqual(uint8_t left, uint8_t right);
void GreaterThanOrEqual(uint8_t left, uint8_t right);
void Increment(uint8_t dest);
void Decrement(uint8_t dest);
void TestNotEqual(uint8_t left, uint8_t right);
void TestEqualNil(uint8_t left);

#endif //_INSTRUCTION_BUFFER_DEF_H_

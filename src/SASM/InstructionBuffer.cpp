#include "InstructionBuffer.hpp"

//Constant region of the instruction buffer
uint8_t* constant;
int currentConstant;
int maxConst;

//Instruction region of the instruction buffer
uint8_t* buffer;
int current;
int maxBuf;

uint8_t* getInstructionBuffer() {
	return buffer;
}

int getInstructionBufferSize() {
	return current;
}

uint8_t* getInstructionConstant() {
	return constant;
}

int getInstructionConstantSize() {
	return currentConstant;
}

void InitInstructionBuffer() {

	if (buffer || constant) {
		DeleteInstructionBuffer();
	}

	constant = new uint8_t[128];
	currentConstant = 0;
	maxConst = 128;

	buffer = new uint8_t[128];
	current = 0;
	maxBuf = 128;
}

void DeleteInstructionBuffer() {

	if (buffer) {
		delete[] buffer;
		buffer = 0;
	}

	if (constant) {
		delete[] constant;
		constant = 0;
	}

	current = 0;
	currentConstant = 0;
	maxConst = 0;
	maxBuf = 0;
}

void GrowConstant(int size) {

	uint8_t* nc = new uint8_t[maxConst + size];

	memcpy(nc, constant, maxConst);

	delete[] constant;
	constant = nc;

	maxConst += size;
}

void GrowBuffer(int size) {

	uint8_t* nb = new uint8_t[maxBuf + size];
	memcpy(nb, buffer, maxBuf);

	delete[] buffer;
	buffer = nb;

	maxBuf += size;
}

uint8_t* PotentialGrow(uint8_t* bfr, int pushSize) {

	if (bfr == buffer && current + pushSize + 1 >= maxBuf) {
		GrowBuffer(128);
		return buffer;
	} else if (bfr == constant && currentConstant + pushSize + 1 >= maxConst) {
		GrowConstant(128);
		return constant;
	}

	return bfr;
}

void Set(uint8_t* inst, int& count, uint8_t val) {
	inst = PotentialGrow(inst, 1);
	inst[count++] = val;
}

void Set(uint8_t* inst, int& count, int val) {

	inst = PotentialGrow(inst, 4);

	*(int*) (inst + count) = val;
	count += 4;
}

void Set(uint8_t* inst, int& count, float32_t val) {

	inst = PotentialGrow(inst, 4);

	*(float32_t*) (inst + count) = val;
	count += 4;
}

void Set(uint8_t* inst, int& count, long lval) {

	inst = PotentialGrow(inst, 8);

	*((long*) (inst + count)) = lval;
	count += 8;
}

void Set(uint8_t* inst, int& count, char const* str) {

	int size = strlen(str) + 1;

	inst = PotentialGrow(inst, size);

	memcpy(inst + count, str, size);
	count += size;
}

void IncreaseCurrent(int size) {
	PotentialGrow(buffer, size);
	current += size;
}

void LoadInt(int val, uint8_t dest) {

	Set(buffer, current, (uint8_t) VM::OpLoadConstant);
	Set(buffer, current, (int) currentConstant);
	Set(buffer, current, (uint8_t) dest);

	Set(constant, currentConstant, (uint8_t) VM::CInt);
	Set(constant, currentConstant, (int) val);

	IncreaseCurrent(2);
}

void LoadFloat32(float32_t val, uint8_t dest) {
	Set(buffer, current, (uint8_t) VM::OpLoadConstant);
	Set(buffer, current, (int) currentConstant);
	Set(buffer, current, (uint8_t) dest);

	Set(constant, currentConstant, (uint8_t) VM::CFloat32);
	Set(constant, currentConstant, (float32_t) val);

	IncreaseCurrent(2);
}

void PopNil() {

	Set(buffer, current, (uint8_t) VM::OpPopNil);

	IncreaseCurrent(7);
}

void ArrayLength(uint8_t reg, uint8_t dst) {
	Set(buffer, current, (uint8_t) VM::OpArrayLength);
	Set(buffer, current, (uint8_t) reg);
	Set(buffer, current, (uint8_t) dst);
	IncreaseCurrent(5);
}

void LoadLong(long val, uint8_t reg) {

	Set(buffer, current, (uint8_t) VM::OpLoadConstant);
	Set(buffer, current, (int) currentConstant);
	Set(buffer, current, (uint8_t) reg);

	Set(constant, currentConstant, (uint8_t) VM::CLong);
	Set(constant, currentConstant, (long) val);

	IncreaseCurrent(2);
}

void CallFunction(char const* name) {
	Set(buffer, current, (uint8_t) VM::OpCallFn);
	Set(buffer, current, (uint8_t) VM::Constant);
	Set(buffer, current, (int) currentConstant);

	Set(constant, currentConstant, name);

	IncreaseCurrent(2);
}

void Return() {
	Set(buffer, current, (uint8_t) VM::OpReturn);
	IncreaseCurrent(7);
}

void PushRegisters(uint8_t start, uint8_t num) {
	Set(buffer, current, (uint8_t) VM::OpPushRegisters);
	Set(buffer, current, (uint8_t) start);
	Set(buffer, current, (uint8_t) num);
	IncreaseCurrent(5);
}

void PopRegisters(uint8_t start, uint8_t num) {
	Set(buffer, current, (uint8_t) VM::OpPopRegisters);
	Set(buffer, current, start);
	Set(buffer, current, num);
	IncreaseCurrent(5);
}

void ArraySet(uint8_t dataReg, uint8_t arrayReg, uint8_t indexReg) {
	Set(buffer, current, (uint8_t) VM::OpArraySet);
	Set(buffer, current, (uint8_t) dataReg);
	Set(buffer, current, (uint8_t) arrayReg);
	Set(buffer, current, (uint8_t) indexReg);
	IncreaseCurrent(4);
}

void ArrayGet(uint8_t arrayReg, uint8_t indexReg, uint8_t dataReg) {
	Set(buffer, current, (uint8_t) VM::OpArrayGet);
	Set(buffer, current, (uint8_t) arrayReg);
	Set(buffer, current, (uint8_t) indexReg);
	Set(buffer, current, (uint8_t) dataReg);
	IncreaseCurrent(4);
}

void Structure(std::string type, uint8_t dst) {
	Set(buffer, current, (uint8_t) VM::OpNewStruct);
	Set(buffer, current, (int) currentConstant);
	Set(buffer, current, (uint8_t) dst);

	const char* typePointer = type.c_str();
	Set(constant, currentConstant, typePointer);

	IncreaseCurrent(2);
}

void StructureFieldSet(uint8_t tgtArray, uint8_t index, uint8_t data) {
	Set(buffer, current, (uint8_t) VM::OpStructSetField);
	Set(buffer, current, (uint8_t) tgtArray);
	Set(buffer, current, (uint8_t) index);
	Set(buffer, current, (uint8_t) data);
	IncreaseCurrent(4);
}

void StructureFieldGet(uint8_t tgtArray, uint8_t index, uint8_t data) {
	Set(buffer, current, (uint8_t) VM::OpStructGetField);
	Set(buffer, current, (uint8_t) tgtArray);
	Set(buffer, current, (uint8_t) index);
	Set(buffer, current, (uint8_t) data);
	IncreaseCurrent(4);
}

void Array(std::string type, uint8_t sizereg, uint8_t reg) {

	Set(buffer, current, (uint8_t) VM::OpNewArray);
	Set(buffer, current, (uint8_t) sizereg);
	Set(buffer, current, (uint8_t) reg);
	Set(buffer, current, (int) currentConstant);

	const char* typePointer = type.c_str();
	Set(constant, currentConstant, typePointer);

	IncreaseCurrent(1);
}

void LoadString(char const* str, uint8_t reg) {

	Set(buffer, current, (uint8_t) VM::OpLoadConstant);
	Set(buffer, current, (int) currentConstant);
	Set(buffer, current, (uint8_t) reg);

	Set(constant, currentConstant, (uint8_t) VM::CArray);
	Set(constant, currentConstant, "string");
	Set(constant, currentConstant, (int) (strlen(str) + 1));
	Set(constant, currentConstant, (int) (strlen(str) + 1));
	Set(constant, currentConstant, str);

	IncreaseCurrent(2);
}

void Add(uint8_t left, uint8_t right, uint8_t dest) {
	Set(buffer, current, (uint8_t) VM::OpAdd);
	Set(buffer, current, left);
	Set(buffer, current, right);
	Set(buffer, current, dest);
	IncreaseCurrent(4);
}

void Subtract(uint8_t left, uint8_t right, uint8_t dest) {
	Set(buffer, current, (uint8_t) VM::OpSub);
	Set(buffer, current, left);
	Set(buffer, current, right);
	Set(buffer, current, dest);
	IncreaseCurrent(4);
}

void Multiply(uint8_t left, uint8_t right, uint8_t dest) {
	Set(buffer, current, (uint8_t) VM::OpMul);
	Set(buffer, current, left);
	Set(buffer, current, right);
	Set(buffer, current, dest);
	IncreaseCurrent(4);
}

void Divide(uint8_t left, uint8_t right, uint8_t dest) {
	Set(buffer, current, (uint8_t) VM::OpDiv);
	Set(buffer, current, left);
	Set(buffer, current, right);
	Set(buffer, current, dest);
	IncreaseCurrent(4);
}

void AddFloat32(uint8_t left, uint8_t right, uint8_t dest) {
	Set(buffer, current, (uint8_t) VM::OpAddFloat32);
	Set(buffer, current, left);
	Set(buffer, current, right);
	Set(buffer, current, dest);
	IncreaseCurrent(4);
}

void SubtractFloat32(uint8_t left, uint8_t right, uint8_t dest) {
	Set(buffer, current, (uint8_t) VM::OpSubFloat32);
	Set(buffer, current, left);
	Set(buffer, current, right);
	Set(buffer, current, dest);
	IncreaseCurrent(4);
}

void MultiplyFloat32(uint8_t left, uint8_t right, uint8_t dest) {
	Set(buffer, current, (uint8_t) VM::OpMulFloat32);
	Set(buffer, current, left);
	Set(buffer, current, right);
	Set(buffer, current, dest);
	IncreaseCurrent(4);
}

void DivideFloat32(uint8_t left, uint8_t right, uint8_t dest) {
	Set(buffer, current, (uint8_t) VM::OpDivFloat32);
	Set(buffer, current, left);
	Set(buffer, current, right);
	Set(buffer, current, dest);
	IncreaseCurrent(4);
}

void CompareFloat32(uint8_t left, uint8_t right, uint8_t dest) {
	Set(buffer, current, (uint8_t) VM::OpCmpFloat32);
	Set(buffer, current, left);
	Set(buffer, current, right);
	Set(buffer, current, dest);
	IncreaseCurrent(4);
}

void Move(uint8_t target, uint8_t dest) {

	Set(buffer, current, (uint8_t) VM::OpMove);
	Set(buffer, current, target);
	Set(buffer, current, dest);
	IncreaseCurrent(5);
}

void JumpDirect(int inst) {
	Set(buffer, current, (uint8_t) VM::OpJump);
	Set(buffer, current, (uint8_t) VM::DirectExact);
	Set(buffer, current, inst);

	IncreaseCurrent(2);
}

void JumpDirectRelative(int inst) {
	Set(buffer, current, (uint8_t) VM::OpJump);
	Set(buffer, current, (uint8_t) VM::DirectRelative);
	Set(buffer, current, inst);
	IncreaseCurrent(2);
}

void JumpRegister(int reg) {
	Set(buffer, current, (uint8_t) VM::OpJump);
	Set(buffer, current, (uint8_t) VM::RegisterExact);
	Set(buffer, current, reg);
	IncreaseCurrent(2);
}

void JumpRegisterRelative(int reg) {
	Set(buffer, current, (uint8_t) VM::OpJump);
	Set(buffer, current, (uint8_t) VM::RegisterRelative);
	Set(buffer, current, reg);
	IncreaseCurrent(2);
}

void TestEqual(uint8_t left, uint8_t right) {
	Set(buffer, current, (uint8_t) VM::OpEqual);
	Set(buffer, current, left);
	Set(buffer, current, right);
	IncreaseCurrent(5);
}

void LessThan(uint8_t left, uint8_t right) {
	Set(buffer, current, (uint8_t) VM::OpLessThan);
	Set(buffer, current, left);
	Set(buffer, current, right);
	IncreaseCurrent(5);
}

void GreaterThan(uint8_t left, uint8_t right) {
	Set(buffer, current, (uint8_t) VM::OpGreaterThan);
	Set(buffer, current, left);
	Set(buffer, current, right);
	IncreaseCurrent(5);
}

void LessThanOrEqual(uint8_t left, uint8_t right) {
	Set(buffer, current, (uint8_t) VM::OpLessThanOrEqual);
	Set(buffer, current, left);
	Set(buffer, current, right);
	IncreaseCurrent(5);
}

void GreaterThanOrEqual(uint8_t left, uint8_t right) {
	Set(buffer, current, (uint8_t) VM::OpGreaterThanOrEqual);
	Set(buffer, current, left);
	Set(buffer, current, right);
	IncreaseCurrent(5);
}

void Increment(uint8_t dest) {
	Set(buffer, current, (uint8_t) VM::OpInc);
	Set(buffer, current, dest);
	IncreaseCurrent(6);
}

void Decrement(uint8_t dest) {
	Set(buffer, current, (uint8_t) VM::OpDec);
	Set(buffer, current, dest);
	IncreaseCurrent(6);
}

void TestNotEqual(uint8_t left, uint8_t right) {
	Set(buffer, current, (uint8_t) VM::OpNotEqual);
	Set(buffer, current, left);
	Set(buffer, current, right);
	IncreaseCurrent(5);
}

void TestEqualNil(uint8_t left) {
	Set(buffer, current, (uint8_t) VM::OpEqualZero);
	Set(buffer, current, left);
	IncreaseCurrent(6);
}

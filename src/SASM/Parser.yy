%error-verbose
%locations
%name-prefix "sasm_"

%{
#include <stdio.h>
#include <string.h>
#include <string>
#include <VM/OpCodes.hpp>
#include <types.h>
#include <VM/Constants.hpp>
#include <VM/InstructionSet.hpp>
#include <VM/ConstantTypes.hpp>
#include <VM/VMNamespace.hpp>
#include <VM/JumpTypes.hpp>
#include <SASM/SasmException.hpp>

int sasm_lex();
void sasm_error(const char* s);

extern int sasm_lineno;	// defined and maintained in lex.c
extern char *sasm_text;	// defined and maintained in lex.c

uint8_t* constant;
int currentConstant;
int maxConst;

uint8_t* buffer;
int current;
int maxBuf;

VM::VMNamespace CurrentNamespace;

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

 *(int*)(inst+count) = val;
 count += 4;
}

void Set(uint8_t* inst, int& count, float32_t val) {

 inst = PotentialGrow(inst, 4);

 *(float32_t*)(inst+count) = val;
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
	Set(constant, currentConstant, (int)(strlen(str) + 1));
	Set(constant, currentConstant, (int)(strlen(str) + 1));
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

%}


%union {
	std::string* string;	
	float32_t float32;
	int integer;
	long lval;
}

%token <string> WORD STRING
%token <float32> FLOAT32
%token <integer> INT REG
%token <lval> LONG
%token LBRACKET RBRACKET STRUCTURE_GET STRUCTURE_SET NEW_STRUCT COMPARE_FLOAT32 INCREMENT DECREMENT ADD_FLOAT32 SUBTRACT_FLOAT32 MULTIPLY_FLOAT32 DIVIDE_FLOAT32 PUSH_REGISTERS POP_REGISTERS TEST_EQUAL_NIL POP_NIL JUMP_RELATIVE CALL_FN LOAD ADD PUSH POP MOVE TEST_EQUAL ARRAY_LENGTH TEST_NOT_EQUAL JUMP RETURN LESS_THAN LESS_THAN_OR_EQUAL ARRAY_SET ARRAY_GET GREATER_THAN GREATER_THAN_OR_EQUAL SUBTRACT MULTIPLY DIVIDE NEW_ARRAY

%type <int> SASMFunction SASMProgram

%start SASMProgram

%%

SASMProgram: {
	CurrentNamespace = VM::VMNamespace();
} | SASMProgram WORD LBRACKET SASMFunction RBRACKET {
	CurrentNamespace.insert(*$2, VM::NamespaceEntry(SmartPointer<VM::VMFunc>(new VM::VMFunc(*$2, VM::InstructionSet(buffer, current, constant, currentConstant, 0)))));
	delete $2;
	
	//Free all the data allocated during parsing and reset all values to 0
   	delete[] buffer;
	buffer = 0;

	delete[] constant;
	constant = 0;
};

SASMFunction: {
		
		constant = new uint8_t[128];
		currentConstant = 0;
		maxConst = 128;
		
		buffer = new uint8_t[128];
		current = 0;
		maxBuf = 128;
		
	} | SASMFunction CALL_FN STRING {
		CallFunction($3->c_str());
		delete $3;
	} | SASMFunction RETURN {
		Return();
	} | SASMFunction ARRAY_SET REG REG REG {
		ArraySet($3, $4, $5);
	} | SASMFunction ARRAY_GET REG REG REG {
		ArrayGet($3, $4, $5);
	} | SASMFunction ARRAY_LENGTH REG REG {
		ArrayLength($3, $4);
	} | SASMFunction NEW_ARRAY STRING REG REG {
		Array(*$3, $4, $5);
		delete $3;
	} | SASMFunction NEW_STRUCT STRING REG {
		Structure(*$3, $4);
		delete $3;
	} | SASMFunction STRUCTURE_SET REG REG REG {
		StructureFieldSet($3, $4, $5);
	} | SASMFunction STRUCTURE_GET REG REG REG {
		StructureFieldGet($3, $4, $5);
	} | SASMFunction PUSH_REGISTERS REG INT {
		PushRegisters($3, $4);
	} | SASMFunction POP_REGISTERS REG INT {
		PopRegisters($3, $4);
	} | SASMFunction POP_NIL {
		PopNil();
	} | SASMFunction LOAD INT REG {
		LoadInt($3, $4);
	} | SASMFunction LOAD FLOAT32 REG {
		LoadFloat32($3, $4);
	} | SASMFunction LOAD LONG REG {
		LoadLong($3, $4);
	} | SASMFunction LOAD STRING REG {
		LoadString($3->c_str(), $4);
		delete $3;
	} | SASMFunction MOVE REG REG {
		Move($3, $4);
	} | SASMFunction INCREMENT REG {
		Increment($3);
	} | SASMFunction DECREMENT REG {
		Decrement($3);
	} | SASMFunction ADD_FLOAT32 REG REG REG {
		AddFloat32($3, $4, $5);
	} | SASMFunction SUBTRACT_FLOAT32 REG REG REG {
		SubtractFloat32($3, $4, $5);
	} | SASMFunction MULTIPLY_FLOAT32 REG REG REG {
		MultiplyFloat32($3, $4, $5);
	} | SASMFunction DIVIDE_FLOAT32 REG REG REG {
		DivideFloat32($3, $4, $5);
	} | SASMFunction COMPARE_FLOAT32 REG REG REG {
		CompareFloat32($3, $4, $5);
	} | SASMFunction ADD REG REG REG {
		Add($3, $4, $5);
	} | SASMFunction SUBTRACT REG REG REG {
		Subtract($3, $4, $5);
	} | SASMFunction MULTIPLY REG REG REG {
		Multiply($3, $4, $5);
	} | SASMFunction DIVIDE REG REG REG {
		Divide($3, $4, $5);
	} | SASMFunction TEST_EQUAL_NIL REG {
		TestEqualNil($3);
	} | SASMFunction TEST_EQUAL REG REG {
		TestEqual($3, $4);
	} | SASMFunction TEST_EQUAL REG INT {
		LoadInt($4, VM::vmTempRegisterOne);
		TestEqual($3, VM::vmTempRegisterOne);
	} | SASMFunction TEST_NOT_EQUAL REG REG {
		TestNotEqual($3, $4);
	} | SASMFunction TEST_NOT_EQUAL REG INT {
		LoadInt($4, VM::vmTempRegisterOne);
		TestNotEqual($3, VM::vmTempRegisterOne);
	} | SASMFunction LESS_THAN REG REG {
		LessThan($3, $4);
	} | SASMFunction LESS_THAN REG INT {
		LoadInt($4, VM::vmTempRegisterOne);
		LessThan($3, VM::vmTempRegisterOne);
	} | SASMFunction GREATER_THAN REG REG {
		GreaterThan($3, $4);
	} | SASMFunction GREATER_THAN REG INT {
		LoadInt($4, VM::vmTempRegisterOne);
		GreaterThan($3, VM::vmTempRegisterOne);
	} | SASMFunction LESS_THAN_OR_EQUAL REG REG {
		LessThanOrEqual($3, $4);
	} | SASMFunction LESS_THAN_OR_EQUAL REG INT {
		LoadInt($4, VM::vmTempRegisterOne);
		LessThanOrEqual($3, VM::vmTempRegisterOne);
	} | SASMFunction GREATER_THAN_OR_EQUAL REG REG {
		GreaterThanOrEqual($3, $4);
	} | SASMFunction GREATER_THAN_OR_EQUAL REG INT {
		LoadInt($4, VM::vmTempRegisterOne);
		GreaterThanOrEqual($3, VM::vmTempRegisterOne);
	} | SASMFunction JUMP INT {
		JumpDirect($3);
	} | SASMFunction JUMP_RELATIVE INT {
		JumpDirectRelative($3);
	} | SASMFunction JUMP REG {
		JumpRegister($3);
	} | SASMFunction JUMP_RELATIVE REG {
		JumpRegisterRelative($3);
	}
;

%%

void sasm_error(std::string s) {
  printf("ERROR: %s at symbol %s on line %i\n", s.c_str(), sasm_text, sasm_lineno);
  throw SasmException(s);
}

void sasm_error(const char* s)
{
  sasm_error(std::string(s));
}

%error-verbose
%locations
%name-prefix "sasm_"

%{
#include <stdio.h>
#include <string.h>
#include <string>
#include <VM/OpCodes.hpp>
#include <stdint.h>
#include <VM/Constants.hpp>
#include <VM/InstructionSet.hpp>
#include <VM/ConstantTypes.hpp>
#include <VM/JumpTypes.hpp>
#include <SASM/SasmException.hpp>

int sasm_lex();
void sasm_error(const char* s);

extern int sasm_lineno;	// defined and maintained in lex.c
extern char *sasm_text;	// defined and maintained in lex.c

uint8_t* constant;
int currentConstant;

uint8_t* buffer;
int current;

void Set(uint8_t* inst, int& current, uint8_t val) {
	inst[current++] = val;
}

void Set(uint8_t* inst, int& current, int val) {
	*(int*)(inst+current) = val;
	current += 4;
}

void Set(uint8_t* inst, int& current, long lval) {
	*((long*) (inst + current)) = lval;
	current += sizeof(long);
}

void Set(uint8_t* inst, int& current, char const* str) {
	int size = strlen(str) + 1;
	memcpy(inst + current, str, size);
	current += size;
}

void LoadInt(int val, uint8_t dest) {

	Set(buffer, current, (uint8_t) VM::OpLoadConstant);
	Set(buffer, current, (int) currentConstant);
	Set(buffer, current, (uint8_t) dest);

	Set(constant, currentConstant, (uint8_t) VM::CInt);
	Set(constant, currentConstant, (int) val);
	
	current += 2;
}

void PopNil() {

	Set(buffer, current, (uint8_t) VM::OpPopNil);

	current += 7;
}

void ArrayLength(uint8_t reg, uint8_t dst) {
	Set(buffer, current, (uint8_t) VM::OpArrayLength);
	Set(buffer, current, (uint8_t) reg);
	Set(buffer, current, (uint8_t) dst);
	current += 5;
}

void LoadLong(long val, uint8_t reg) {

	Set(buffer, current, (uint8_t) VM::OpLoadConstant);
	Set(buffer, current, (int) currentConstant);
	Set(buffer, current, (uint8_t) reg);

	Set(constant, currentConstant, (uint8_t) VM::CLong);
	Set(constant, currentConstant, (long) val);
	
	current += 2;
}

void CallFunction(char const* name) {
	Set(buffer, current, (uint8_t) VM::OpCallFn);
	Set(buffer, current, (uint8_t) VM::Constant);
	Set(buffer, current, (int) currentConstant);
	
	Set(constant, currentConstant, name);
	
	current += 2;
}

void Return() {
	Set(buffer, current, (uint8_t) VM::OpReturn);
	current += 7;
}

void PushRegisters(uint8_t start, uint8_t num) {
	Set(buffer, current, (uint8_t) VM::OpPushRegisters);
	Set(buffer, current, (uint8_t) start);
	Set(buffer, current, (uint8_t) num);
	current += 5;
}

void PopRegisters(uint8_t start, uint8_t num) {
	Set(buffer, current, (uint8_t) VM::OpPopRegisters);
	Set(buffer, current, start);
	Set(buffer, current, num);
	current += 5;
}

void ArraySet(uint8_t dataReg, uint8_t arrayReg, uint8_t indexReg) {
	Set(buffer, current, (uint8_t) VM::OpArraySet);
	Set(buffer, current, (uint8_t) dataReg);
	Set(buffer, current, (uint8_t) arrayReg);
	Set(buffer, current, (uint8_t) indexReg);
	current += 4;
}

void ArrayGet(uint8_t arrayReg, uint8_t indexReg, uint8_t dataReg) {
	Set(buffer, current, (uint8_t) VM::OpArrayGet);
	Set(buffer, current, (uint8_t) arrayReg);
	Set(buffer, current, (uint8_t) indexReg);
	Set(buffer, current, (uint8_t) dataReg);
	current += 4;
}

void Array(std::string type, uint8_t sizereg, uint8_t reg) {

	Set(buffer, current, (uint8_t) VM::OpNewArray);
	Set(buffer, current, (uint8_t) sizereg);
	Set(buffer, current, (uint8_t) reg);
	Set(buffer, current, (int) currentConstant);

	const char* typeCstr = type.c_str();
	Set(constant, currentConstant, typeCstr);
	
	current += 1;
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
	
	current += 2;
}

void Add(uint8_t left, uint8_t right, uint8_t dest) {
	Set(buffer, current, (uint8_t) VM::OpAdd);
	Set(buffer, current, left);
	Set(buffer, current, right);
	Set(buffer, current, dest);
	current += 4;
}

void Subtract(uint8_t left, uint8_t right, uint8_t dest) {
	Set(buffer, current, (uint8_t) VM::OpSub);
	Set(buffer, current, left);
	Set(buffer, current, right);
	Set(buffer, current, dest);
	current += 4;
}

void Multiply(uint8_t left, uint8_t right, uint8_t dest) {
	Set(buffer, current, (uint8_t) VM::OpMul);
	Set(buffer, current, left);
	Set(buffer, current, right);
	Set(buffer, current, dest);
	current += 4;
}


void Divide(uint8_t left, uint8_t right, uint8_t dest) {
	Set(buffer, current, (uint8_t) VM::OpDiv);
	Set(buffer, current, left);
	Set(buffer, current, right);
	Set(buffer, current, dest);
	current += 4;
}


void Move(uint8_t target, uint8_t dest) {

	Set(buffer, current, (uint8_t) VM::OpMove);
	Set(buffer, current, target);
	Set(buffer, current, dest);
	current += 5;
}

void JumpDirect(int inst) {
	Set(buffer, current, (uint8_t) VM::OpJump);
	Set(buffer, current, (uint8_t) VM::DirectExact);
	Set(buffer, current, inst);
	
	current += 2;
}

void JumpDirectRelative(int inst) {
	Set(buffer, current, (uint8_t) VM::OpJump);
	Set(buffer, current, (uint8_t) VM::DirectRelative);
	Set(buffer, current, inst);
	current += 2;
}

void JumpRegister(int reg) {
	Set(buffer, current, (uint8_t) VM::OpJump);
	Set(buffer, current, (uint8_t) VM::RegisterExact);
	Set(buffer, current, reg);
	current += 2;
}

void JumpRegisterRelative(int reg) {
	Set(buffer, current, (uint8_t) VM::OpJump);
	Set(buffer, current, (uint8_t) VM::RegisterRelative);
	Set(buffer, current, reg);
	current += 2;
}

void TestEqual(uint8_t left, uint8_t right) {
	Set(buffer, current, (uint8_t) VM::OpEqual);
	Set(buffer, current, left);
	Set(buffer, current, right);
	current += 5;
}

void LessThan(uint8_t left, uint8_t right) {
	Set(buffer, current, (uint8_t) VM::OpLessThan);
	Set(buffer, current, left);
	Set(buffer, current, right);
	current += 5;
}

void GreaterThan(uint8_t left, uint8_t right) {
	Set(buffer, current, (uint8_t) VM::OpLessThanOrEqual);
	Set(buffer, current, left);
	Set(buffer, current, right);
	current += 5;
	JumpDirectRelative(2);
}

void LessThanOrEqual(uint8_t left, uint8_t right) {
	Set(buffer, current, (uint8_t) VM::OpLessThanOrEqual);
	Set(buffer, current, left);
	Set(buffer, current, right);
	current += 5;
}

void GreaterThanOrEqual(uint8_t left, uint8_t right) {
	Set(buffer, current, (uint8_t) VM::OpLessThan);
	Set(buffer, current, left);
	Set(buffer, current, right);
	current += 5;
	JumpDirectRelative(2);
}

void TestNotEqual(uint8_t left, uint8_t right) {
	Set(buffer, current, (uint8_t) VM::OpEqual);
	Set(buffer, current, left);
	Set(buffer, current, right);
	current += 5;
	JumpDirectRelative(2);
}

void TestEqualNil(uint8_t left) {
	Set(buffer, current, (uint8_t) VM::OpEqualZero);
	Set(buffer, current, left);
	current += 6;
}

%}


%union {
	std::string* string;	
	float real;
	int integer;
	long lval;
}

%token <string> WORD STRING
%token <real> REAL
%token <integer> INT REG
%token <lval> LONG
%token PUSH_REGISTERS POP_REGISTERS TEST_EQUAL_NIL POP_NIL JUMP_RELATIVE CALL_FN LOAD ADD PUSH POP MOVE TEST_EQUAL ARRAY_LENGTH TEST_NOT_EQUAL JUMP RETURN LESS_THAN LESS_THAN_OR_EQUAL ARRAY_SET ARRAY_GET GREATER_THAN GREATER_THAN_OR_EQUAL SUBTRACT MULTIPLY DIVIDE NEW_ARRAY

%type <int> Program

%start Program

%%

Program: {
		
		constant = new uint8_t[4000];
		currentConstant = 0;
		
		buffer = new uint8_t[5000];
		current = 0;
		
	} | Program CALL_FN STRING {
		CallFunction($3->c_str());
		delete $3;
	} | Program RETURN {
		Return();
	} | Program ARRAY_SET REG REG REG {
		ArraySet($3, $4, $5);
	} | Program ARRAY_GET REG REG REG {
		ArrayGet($3, $4, $5);
	} | Program ARRAY_LENGTH REG REG {
		ArrayLength($3, $4);
	} | Program NEW_ARRAY STRING INT REG {
		LoadInt($4, 3);
		Array(*$3, 3, $5);
		delete $3;
	} | Program PUSH_REGISTERS REG INT {
		PushRegisters($3, $4);
	} | Program POP_REGISTERS REG INT {
		PopRegisters($3, $4);
	} | Program POP_NIL {
		PopNil();
	} | Program NEW_ARRAY STRING REG REG {
		Array(*$3, $4, $5);
		delete $3;
	} | Program LOAD INT REG {
		LoadInt($3, $4);
	} | Program LOAD LONG REG {
		LoadLong($3, $4);
	} | Program LOAD STRING REG {
		LoadString($3->c_str(), $4);
		delete $3;
	} | Program MOVE REG REG {
		Move($3, $4);
	} | Program ADD REG REG REG {
		Add($3, $4, $5);
	} | Program ADD REG INT REG {
		LoadInt($4, VM::vmTempRegisterOne);
		Add($3, VM::vmTempRegisterOne, $5);
	} | Program ADD INT INT REG {
		LoadInt($3, VM::vmTempRegisterOne);
		LoadInt($4, VM::vmTempRegisterTwo);
		Add(VM::vmTempRegisterOne, VM::vmTempRegisterTwo, $5);
	} | Program SUBTRACT REG REG REG {
		Subtract($3, $4, $5);
	} | Program SUBTRACT REG INT REG {
		LoadInt($4, VM::vmTempRegisterOne);
		Subtract($3, VM::vmTempRegisterOne, $5);
	} | Program SUBTRACT INT INT REG {
		LoadInt($3, VM::vmTempRegisterOne);
		LoadInt($4, VM::vmTempRegisterTwo);
		Subtract(VM::vmTempRegisterOne, VM::vmTempRegisterTwo, $5);
	} | Program MULTIPLY REG REG REG {
		Multiply($3, $4, $5);
	} | Program MULTIPLY REG INT REG {
		LoadInt($4, VM::vmTempRegisterOne);
		Multiply($3, VM::vmTempRegisterOne, $5);
	} | Program MULTIPLY INT INT REG {
		LoadInt($3, VM::vmTempRegisterOne);
		LoadInt($4, VM::vmTempRegisterTwo);
		Multiply(VM::vmTempRegisterOne, VM::vmTempRegisterTwo, $5);
	} | Program DIVIDE REG REG REG {
		Divide($3, $4, $5);
	} | Program DIVIDE REG INT REG {
		LoadInt($4, VM::vmTempRegisterOne);
		Divide($3, VM::vmTempRegisterOne, $5);
	} | Program DIVIDE INT INT REG {
		LoadInt($3, VM::vmTempRegisterOne);
		LoadInt($4, VM::vmTempRegisterTwo);
		Divide(VM::vmTempRegisterOne, VM::vmTempRegisterTwo, $5);
	} | Program TEST_EQUAL_NIL REG {
		TestEqualNil($3);
	} | Program TEST_EQUAL REG REG {
		TestEqual($3, $4);
	} | Program TEST_EQUAL REG INT {
		LoadInt($4, VM::vmTempRegisterOne);
		TestEqual($3, VM::vmTempRegisterOne);
	} | Program TEST_NOT_EQUAL REG REG {
		TestNotEqual($3, $4);
	} | Program TEST_NOT_EQUAL REG INT {
		LoadInt($4, VM::vmTempRegisterOne);
		TestNotEqual($3, VM::vmTempRegisterOne);
	} | Program LESS_THAN REG REG {
		LessThan($3, $4);
	} | Program LESS_THAN REG INT {
		LoadInt($4, VM::vmTempRegisterOne);
		LessThan($3, VM::vmTempRegisterOne);
	} | Program GREATER_THAN REG REG {
		GreaterThan($3, $4);
	} | Program GREATER_THAN REG INT {
		LoadInt($4, VM::vmTempRegisterOne);
		GreaterThan($3, VM::vmTempRegisterOne);
	} | Program LESS_THAN_OR_EQUAL REG REG {
		LessThanOrEqual($3, $4);
	} | Program LESS_THAN_OR_EQUAL REG INT {
		LoadInt($4, VM::vmTempRegisterOne);
		LessThanOrEqual($3, VM::vmTempRegisterOne);
	} | Program GREATER_THAN_OR_EQUAL REG REG {
		GreaterThanOrEqual($3, $4);
	} | Program GREATER_THAN_OR_EQUAL REG INT {
		LoadInt($4, VM::vmTempRegisterOne);
		GreaterThanOrEqual($3, VM::vmTempRegisterOne);
	} | Program JUMP INT {
		JumpDirect($3);
	} | Program JUMP_RELATIVE INT {
		JumpDirectRelative($3);
	} | Program JUMP REG {
		JumpRegister($3);
	} | Program JUMP_RELATIVE REG {
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

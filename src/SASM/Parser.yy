%error-verbose
%locations
%name-prefix "sasm_"

%{
#include <string>
#include <VM/OpCodes.hpp>
#include <stdint.h>
#include <VM/VirtualMachine.hpp>
#include <VM/InstructionSet.hpp>
#include <VM/ConstantTypes.hpp>
#include <VM/JumpTypes.hpp>

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

void LoadInt(int val, uint8_t dest) {

	Set(buffer, current, (uint8_t) VM::OpLoadConstant);
	Set(buffer, current, (int) currentConstant);
	Set(buffer, current, (uint8_t) dest);

	Set(constant, currentConstant, (uint8_t) VM::CInt);
	Set(constant, currentConstant, (int) val);
}

void LoadLong(long val, uint8_t reg) {

	Set(buffer, current, (uint8_t) VM::OpLoadConstant);
	Set(buffer, current, (int) currentConstant);
	Set(buffer, current, (uint8_t) reg);

	Set(constant, currentConstant, (uint8_t) VM::CLong);
	Set(constant, currentConstant, (long) val);
}

void Add(uint8_t left, uint8_t right, uint8_t dest) {
	Set(buffer, current, (uint8_t) VM::OpAdd);
	Set(buffer, current, left);
	Set(buffer, current, right);
	Set(buffer, current, dest);
	current += 2;
}

void Move(uint8_t target, uint8_t dest) {

	Set(buffer, current, (uint8_t) VM::OpMove);
	Set(buffer, current, target);
	Set(buffer, current, dest);
	
	current += 3;
}

void JumpDirect(int inst) {
	Set(buffer, current, (uint8_t) VM::OpJump);
	Set(buffer, current, (uint8_t) VM::DirectExact);
	Set(buffer, current, inst);
}

void JumpDirectRelative(int inst) {
	Set(buffer, current, (uint8_t) VM::OpJump);
	Set(buffer, current, (uint8_t) VM::DirectRelative);
	Set(buffer, current, inst);
}

void JumpRegister(int reg) {
	Set(buffer, current, (uint8_t) VM::OpJump);
	Set(buffer, current, (uint8_t) VM::RegisterExact);
	Set(buffer, current, reg);
}

void JumpRegisterRelative(int reg) {
	Set(buffer, current, (uint8_t) VM::OpJump);
	Set(buffer, current, (uint8_t) VM::RegisterRelative);
	Set(buffer, current, reg);
}

void TestEqual(uint8_t left, uint8_t right) {
	Set(buffer, current, (uint8_t) VM::OpEqual);
	Set(buffer, current, left);
	Set(buffer, current, right);
	current += 3;
}

void LessThan(uint8_t left, uint8_t right) {
	Set(buffer, current, (uint8_t) VM::OpLessThan);
	Set(buffer, current, left);
	Set(buffer, current, right);
	current += 3;
}

void GreaterThan(uint8_t left, uint8_t right) {
	Set(buffer, current, (uint8_t) VM::OpLessThanOrEqual);
	Set(buffer, current, left);
	Set(buffer, current, right);
	current += 3;
	JumpDirectRelative(2);
}

void LessThanOrEqual(uint8_t left, uint8_t right) {
	Set(buffer, current, (uint8_t) VM::OpLessThanOrEqual);
	Set(buffer, current, left);
	Set(buffer, current, right);
	current += 3;
}

void GreaterThanOrEqual(uint8_t left, uint8_t right) {
	Set(buffer, current, (uint8_t) VM::OpLessThan);
	Set(buffer, current, left);
	Set(buffer, current, right);
	current += 3;
	JumpDirectRelative(2);
}

void TestNotEqual(uint8_t left, uint8_t right) {
	Set(buffer, current, (uint8_t) VM::OpEqual);
	Set(buffer, current, left);
	Set(buffer, current, right);
	current += 3;
	JumpDirectRelative(2);
}

void Return() {
	Set(buffer, current, (uint8_t) VM::OpReturn);
	current += 5;
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
%token JUMP_RELATIVE LOAD ADD PUSH POP MOVE TEST_EQUAL TEST_NOT_EQUAL JUMP RETURN LESS_THAN LESS_THAN_OR_EQUAL GREATER_THAN GREATER_THAN_OR_EQUAL

%type <int> Program

%start Program

%%

Program: {
		
		constant = new uint8_t[4000];
		currentConstant = 0;
		
		buffer = new uint8_t[5000];
		current = 0;
		
	} | Program LOAD INT REG {
		LoadInt($3, $4);
	} | Program LOAD LONG REG {
		LoadLong($3, $4);
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
	} | Program RETURN {
		Return();
	}
;

%%

void sasm_error(std::string s) {
  printf("ERROR: %s at symbol %s on line %i\n", s.c_str(), sasm_text, sasm_lineno);
}

void sasm_error(const char* s)
{
  sasm_error(std::string(s));
}

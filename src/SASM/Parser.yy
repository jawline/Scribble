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

void LoadInt(uint8_t reg, int val) {

	Set(buffer, current, (uint8_t) VM::OpLoadConstant);
	Set(buffer, current, (uint8_t) reg);
	Set(buffer, current, (int) currentConstant);

	Set(constant, currentConstant, (uint8_t) VM::CInt);
	Set(constant, currentConstant, (int) val);
}

void LoadLong(uint8_t reg, long val) {

	Set(buffer, current, (uint8_t) VM::OpLoadConstant);
	Set(buffer, current, (uint8_t) reg);
	Set(buffer, current, (int) currentConstant);

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

void TestEqual(uint8_t left, uint8_t right) {
	Set(buffer, current, (uint8_t) VM::OpTestEqual);
	Set(buffer, current, left);
	Set(buffer, current, right);
	current += 3;
}

void TestNotEqual(uint8_t left, uint8_t right) {
	Set(buffer, current, (uint8_t) VM::OpTestNotEqual);
	Set(buffer, current, left);
	Set(buffer, current, right);
	current += 3;
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
%token <integer> INT
%token <lval> LONG
%token LOAD REG ADD PUSH POP MOVE TEST_EQUAL TEST_NOT_EQUAL JUMP RETURN

%type <int> Program

%start Program

%%

Program: {
		
		constant = new uint8_t[4000];
		currentConstant = 0;
		
		buffer = new uint8_t[5000];
		current = 0;
		
	} | Program LOAD INT REG INT {
		LoadInt($5, $3);
	} | Program LOAD LONG REG INT {
		LoadLong($5, $3);
	} | Program MOVE REG INT REG INT {
		Move($4, $6);
	} | Program ADD REG INT REG INT REG INT {
		Add($4, $6, $8);
	} | Program ADD REG INT INT REG INT {
		LoadInt(VM::vmTempRegisterOne, $5);
		Add($4, VM::vmTempRegisterOne, $7);
	} | Program ADD INT INT REG INT {
		LoadInt(VM::vmTempRegisterOne, $3);
		LoadInt(VM::vmTempRegisterTwo, $4);
		Add(VM::vmTempRegisterOne, VM::vmTempRegisterTwo, $6);
	} | Program TEST_EQUAL REG INT REG INT {
		TestEqual($4, $6);
	} | Program TEST_EQUAL REG INT INT {
		LoadInt(VM::vmTempRegisterOne, $5);
		TestEqual($4, VM::vmTempRegisterOne);
	} | Program TEST_NOT_EQUAL REG INT REG INT {
		TestNotEqual($4, $6);
	} | Program TEST_NOT_EQUAL REG INT INT {
		LoadInt(VM::vmTempRegisterOne, $5);
		TestNotEqual($4, VM::vmTempRegisterOne);
	} | Program JUMP INT {
		JumpDirect($3);
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

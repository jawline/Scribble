%error-verbose
%locations
%name-prefix "sasm_"

%{
#include <stdio.h>
#include <string.h>
#include <string>
#include <types.h>
#include <VM/InstructionSet.hpp>
#include <VM/VMNamespace.hpp>
#include <SASM/SasmException.hpp>
#include <SASM/InstructionBuffer.hpp>

int sasm_lex();
void sasm_error(const char* s);

extern int sasm_lineno;	// defined and maintained in lex.c
extern char *sasm_text;	// defined and maintained in lex.c

VM::VMNamespace CurrentNamespace;

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
	CurrentNamespace.insert(*$2, VM::NamespaceEntry(SmartPointer<VM::VMFunc>(new VM::VMFunc(*$2, VM::InstructionSet(getInstructionBuffer(), getInstructionBufferSize(), getInstructionConstant(), getInstructionConstantSize(), 0)))));
	delete $2;
	DeleteInstructionBuffer();
};

SASMFunction: {
		InitInstructionBuffer();
	} | SASMFunction CALL_FN STRING {
		CallFunction($3->c_str());
		delete $3;
	} | SASMFunction CALL_FN REG {
		CallFunctionFromRegister($3);
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

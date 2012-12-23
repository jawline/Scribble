#include <VirtualMachine/VirtualMachine.hpp>

int PushInt(unsigned char* instructions, int current, int value) {
	instructions[current] = LoadConstOp;
	current++;
	instructions[current] = ByteInt;
	current++;
	*((int*)(instructions+current)) = value;
	current += sizeof(int);
	return current;
}

int Add(unsigned char* instructions, int current) {
	instructions[current] = AddOp;
	current++;
	return current;
}

int Subtract(unsigned char* instructions, int current) {
	instructions[current] = SubtractOp;
	current++;
	return current;
}

int Divide(unsigned char* instructions, int current) {
	instructions[current] = DivideOp;
	current++;
	return current;	
}

int Multiply(unsigned char* instructions, int current) {
	instructions[current] = MultiplyOp;
	current++;
	return current;	
}


extern int yylex();
extern void yyparse();
extern FILE* yyin;

int main(int argc, char** argv) {

/**
	int c = 0;
	unsigned char* instructions = new unsigned char[4096];
	c = PushInt(instructions, c, 12);
	c = PushInt(instructions, c, 24);
	c = Add(instructions, c);
	c = PushInt(instructions, c, 9);
	c = Add(instructions, c);
	c = PushInt(instructions, c, 5);
	c = Subtract(instructions, c);
	c = PushInt(instructions, c, 2);
	c = Divide(instructions, c);
	c = PushInt(instructions, c, 5);
	c = Multiply(instructions, c);

	for (int i = 0; i < c; i++) {
		printf("%i ", instructions[i]);
	}
	printf("\n");


	SP<InstructionList> aList = new InstructionList(instructions, c);

	VirtualMachine a;
	a.setInstructions(aList);

	a.execute();
*/

	// open a file handle to a particular file:
	FILE *myfile = fopen("test.scribble", "r");

	// make sure it's valid:
	if (!myfile) {
		printf("unable to open input\n");
		return -1;
	}

	// set lex to read from it instead of defaulting to STDIN:
	yyin = myfile;
	
	// lex through the input:
	yyparse();
	printf("Exit\n");
}

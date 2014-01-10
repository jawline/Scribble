#include <stdio.h>
#include <Scribble/Scribble.hpp>

int main(int argc, char** argv) {
	printf("Hello World from native code\n");
	Scribble sc = Scribble("./test.sc");
	sc.execute("test");

	API::APIValue Mathd = sc.execute("DoMath");
	API::APIValue Boold = sc.execute("DoBool");

	printf("Bool value from scribble in native code: %s\n", Boold.getValueBoolean() ? "true" : "false");
	printf("Int value from scribble in native code: %i\n", Mathd.getValue32());
}

#include <stdio.h>
#include <Scribble/Scribble.hpp>

int main(int argc, char** argv) {
	printf("Hello World from native code\n");

	Scribble sc = Scribble("./test.sc");
	sc.execute("test");


	API::APIValue Mathd = sc.execute("DoMath");
	API::APIValue Boold = sc.execute("DoBool");
	API::APIValue Stringd = sc.execute("DoString");
	API::APIValue Stringd2 = sc.execute("DoStringTwo");

	printf("String value from scribble in native code: %s\n", Stringd.getValueString());
	printf("String value from scribble in native code: %s\n", Stringd2.getValueString());
	printf("Int value from scribble in native code: %i\n", Mathd.getValue32());
	printf("Bool value from scribble in native code: %s\n", Boold.getValueBoolean() ? "true" : "false");
}

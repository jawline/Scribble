#include <stdio.h>
#include <Scribble/Scribble.hpp>

int main(int argc, char** argv) {
	printf("Hello World from native code\n");

	Scribble sc = Scribble("./test.sc");

	std::vector<API::APIValue> args;

	API::APIValue Testd = sc.execute("test", args);
	API::APIValue Mathd = sc.execute("DoMath", args);
	API::APIValue Boold = sc.execute("DoBool", args);
	API::APIValue Stringd = sc.execute("DoString", args);
	API::APIValue Stringd2 = sc.execute("DoStringTwo", args);

	args.push_back(API::APIValue(getIntType(), 4));

	API::APIValue Factoriald = sc.execute("DoFactorial", args);

	printf("String value from scribble in native code: %s\n", Stringd.getValueString());
	printf("String value from scribble in native code: %s\n", Stringd2.getValueString());
	printf("Int value from scribble in native code: %i\n", Mathd.getValue32());
	printf("Bool value from scribble in native code: %s\n", Boold.getValueBoolean() ? "true" : "false");
	printf("Factorial function result passed from Scribble to native: %i\n", Factoriald.getValue32());
}

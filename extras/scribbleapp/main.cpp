#include <stdio.h>
#include <Scribble/Scribble.hpp>

int main(int argc, char** argv) {
	printf("Hello World from native code\n");
	Scribble sc = Scribble("./test.sc");
	sc.execute("test");
}

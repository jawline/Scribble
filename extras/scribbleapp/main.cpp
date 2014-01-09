#include <stdio.h>
#include <Scribble/Scribble.hpp>

int main(int argc, char** argv) {
	printf("Hello World\n");
	Scribble sc = Scribble("./test.sc");
	sc.execute("target.test();");
}

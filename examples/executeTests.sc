/**
 * Scribble tests execution file
 * Copyright (c) Blake Loring 2013
 */

package sys := import("sys");
package loopsTest := import("tests/loops");
package logicalTest := import("tests/logical");
package variablesTest := import("tests/variables");
package recursionTest := import("tests/recursion");
package arraysTest := import("tests/arrays");
package primesTest := import("tests/primes");
package sortsTest := import("tests/sorts");
package floatsTest := import("tests/floats");
package powTest := import("tests/pow");

type Test := struct {
	a : float32;
	b : string;
	c : int;
	d : bool;
	e : Test;
}

/**
 * This is a comment
 * Extra line
 */

func main() {

    loopsTest.Test();
    arraysTest.Test();
    variablesTest.Test();
    recursionTest.Test();
    primesTest.Test();
    logicalTest.Test();
    sortsTest.Test();
    floatsTest.Test();
    powTest.Test();

}

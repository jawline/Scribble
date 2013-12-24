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
package mathTest := import("tests/math");

type Dog := struct {
	a : int;
	b : int;
	c : Cat;
}

type Cat := struct {
	name : string;
}

/**
 * This is a comment
 * Extra line
 */

func main() {

 var J := Dog { 0, 0, Cat { "Phillip" } };

    loopsTest.Test();
    arraysTest.Test();
    variablesTest.Test();
    recursionTest.Test();
    primesTest.Test();
    logicalTest.Test();
    sortsTest.Test();
    floatsTest.Test();
    mathTest.Test();

}

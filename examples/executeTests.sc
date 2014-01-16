/**
 * Scribble tests execution file
 * Copyright (c) Blake Loring 2013
 */

package loopsTest := import("tests/loops");
package logicalTest := import("tests/logical");
package variablesTest := import("tests/variables");
package recursionTest := import("tests/recursion");
package arraysTest := import("tests/arrays");
package primesTest := import("tests/primes");
package sortsTest := import("tests/sorts");
package floatsTest := import("tests/floats");
package mathTest := import("tests/math");
package structTest := import("tests/structures");

package console := import("console");
package sys := import("sys");

type J := struct {
 name : string,
 age : int
}

func PrintJ(x : J) : J {
 console.Log(x->name);
 console.Log(sys.String(x->age));
 return x;
}

/**
 * The main function executes all of the Scribble unit tests.
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
 mathTest.Test();
 structTest.Test();
}

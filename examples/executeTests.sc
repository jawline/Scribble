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
package structQs := import("tests/structQuicksortTest");
package refEqTest := import("tests/refEqualityTest");

package sys := import("sys");
package console := import("console");

/**
 * The main function executes all of the Scribble unit tests.
 */
 
func main() {

 if nil = nil then console.Log("Nil equals nil\n");
 if [100]int = nil then console.Log("Oooo\n");
 var j : array(int);
 if j = nil then console.Log("Hahaha j\n");

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
 structQs.Test();
 refEqTest.Test();

}

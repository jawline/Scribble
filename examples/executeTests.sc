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

type J := struct {
 payload : int,
 next : J
}

func PrintJ(j : J) {
 if j = nil then return;

 console.Log(sys.String(j->payload) $ "\n");
 PrintJ(j->next);
}

/**
 * The main function executes all of the Scribble unit tests.
 */
 
func main() {

 var p := J{5, J { 10, J { 15, J { 20, nil } } } };
 console.Log(sys.String(PrintJ(p)));

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

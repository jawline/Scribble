/**
 * Test Manager manages the testing suite
 */

package console := import("console");

package loopsTest := import("loops");
package logicalTest := import("logical");
package variablesTest := import("variables");
package recursionTest := import("recursion");
package arraysTest := import("arrays");
package primesTest := import("primes");
package sortsTest := import("sorts");
package floatsTest := import("floats");
package mathTest := import("math");
package structTest := import("structures");
package structQs := import("structQuicksortTest");
package refEqTest := import("refEqualityTest");
package listTest := import("LinkedList");

func TestAll() {

 console.Log("Loop Test\n");
 loopsTest.Test();

 console.Log("Arrays Test\n");
 arraysTest.Test();

 console.Log("Variables Test\n");
 variablesTest.Test();

 console.Log("Recursion Test\n");
 recursionTest.Test();

 console.Log("Primes Test\n");
 primesTest.Test();

 console.Log("Logical Test\n");
 logicalTest.Test();

 console.Log("Sorts Test\n");
 sortsTest.Test();

 console.Log("Floats Test\n");
 floatsTest.Test();

 console.Log("Math Test\n");
 mathTest.Test();

 console.Log("Struct Test\n");
 structTest.Test();

 console.Log("Struct Quicksort Test\n");
 structQs.Test();

 console.Log("Reference Equality test\n");
 refEqTest.Test();

 console.Log("List Test\n");
 listTest.Test();

}


/**
 * If executed as a program then run TestAll
 */

func main() {
	TestAll();
}

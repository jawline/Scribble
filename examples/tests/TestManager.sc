/**
 * Test Manager manages the testing suite
 */
package console       := import("console"),
	    notTest       := import("not"),
	    loopsTest     := import("loops"),
	    logicalTest   := import("logical"),
	    variablesTest := import("variables"),
	    recursionTest := import("recursion"),
	    arraysTest    := import("arrays"),
	    primesTest    := import("primes"),
	    sortsTest     := import("sorts"),
	    floatsTest    := import("floats"),
	    mathTest      := import("math"),
	    structTest    := import("structures"),
	    structQs      := import("structQuicksortTest"),
	    refEqTest     := import("refEqualityTest"),
	    listTest      := import("LinkedList"),
	    functionRefs  := import("functionRefs"),
	    assignments   := import("assignments"),
	    magicTest     := import("magicTest"),
	    vectorTest    := import("vector");

func TestAll() {
 console.Log("Not Test\n");
 notTest.Test();

 console.Log("Assignments\n");
 assignments.Test();

 console.Log("Magic numbers test\n");
 magicTest.Test();

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

 console.Log("Function References\n");
 functionRefs.Test();

 console.Log("Vectors\n");
 vectorTest.Test();
 
 console.Log("End of tests\n");
}


/**
 * If executed as a program then run TestAll
 */
func main() {
	TestAll();
}

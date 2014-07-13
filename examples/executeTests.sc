/**
 * Scribble tests execution file
 * Copyright (c) Blake Loring 2013
 */

package sys := import("sys");
package console := import("console");
package tests := import("tests/TestManager");

func Q() {
 console.Log("Hello? This is Q\n");
}

func T(x:int):int{
 console.Log(sys.String(x) $ "\n");

 console.Log("Testing\n");
 Q();
 console.Log("Returning now\n");
}

/**
 * The main function executes all of the Scribble unit tests.
 */
 
func main() {

 var j := &T(int);
 var r := j(10);

 console.Log("And we are back!\n");

 tests.TestAll();
}

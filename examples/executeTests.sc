/**
 * Scribble tests execution file
 * Copyright (c) Blake Loring 2013
 */

package sys := import("sys");
package console := import("console");
package tests := import("tests/TestManager");

func T(x:int) {
}

/**
 * The main function executes all of the Scribble unit tests.
 */
 
func main() {

 var j := &T(int);
 j();

 tests.TestAll();
}

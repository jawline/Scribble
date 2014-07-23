/**
 * Scribble tests execution file
 * Copyright (c) Blake Loring 2013
 */

package sys := import("sys");
package console := import("console");
package tests := import("tests/TestManager");

/**
 * The main function executes all of the Scribble unit tests.
 */
 
func main() {
 tests.TestAll();
}

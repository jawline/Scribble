/**
 * Scribble tests execution file
 * Copyright (c) Blake Loring 2013
 */
package sys     := import("sys"),
        console := import("console"),
        tests   := import("tests/TestManager");

/**
 * The main function executes all of the Scribble unit tests.
 */
func main() {
 tests.TestAll();
}

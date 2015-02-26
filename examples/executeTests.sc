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

 for var i:int between 0 and 10 do {
  console.Log(sys.String(i) $ " Hello World\n");
 }

 tests.TestAll();
}

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

func DoubleAndQ(x:int):int{
 Q();
 return 2*x;
}

func RunDouble(x:int,fn:func(int):int):int {
  return fn(x);
}

/**
 * The main function executes all of the Scribble unit tests.
 */
 
func main() {

 var j := &DoubleAndQ(int);

 console.Log("Doubling 150 using pointerz\n");
 var r := j(150);

 console.Log("This some fancy shit! " $ sys.String(r) $ "\n");

 console.Log("And we are back!\n");

 tests.TestAll();
}

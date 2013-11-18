/**
 * Scribble tests execution file
 * Copyright (c) Blake Loring 2013
 */

package sys := import("sys");
package loopsTest := import("tests/loops");
package logicalTest := import("tests/logical");
package variablesTest := import("tests/variables");
package recursionTest := import("tests/recursion");
package arraysTest := import("tests/arrays");
package primesTest := import("tests/primes");
package sortsTest := import("tests/sorts");
package floatsTest := import("tests/floats");
package vector := import("graphics/vector");

/**
 * This is a comment
 * Extra line
 */

func main() {

	var j := vector.Vector3 { 0f, 10f, 0f };
	
	var r := vector.Vector3 { 10f, 0f, 10f };
	
	var z := vector.Vector3 { 0f, 1f, 0f };
	
	var t := vector.Cross(vector.Add(r, j), z);
	r := vector.Cross(z, vector.Add(r, j));
	
	vector.Debug(t);
	vector.Debug(r);
   
    loopsTest.Test();
    arraysTest.Test();
    variablesTest.Test();
    recursionTest.Test();
    primesTest.Test();
    logicalTest.Test();
    sortsTest.Test();
    floatsTest.Test();

}

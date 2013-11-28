/**
 * Scribble tests execution file
 * Copyright (c) Blake Loring 2013
 */


/**
package sys := import("sys");
package loopsTest := import("tests/loops");
package logicalTest := import("tests/logical");
package variablesTest := import("tests/variables");
package recursionTest := import("tests/recursion");
package arraysTest := import("tests/arrays");
package primesTest := import("tests/primes");
package sortsTest := import("tests/sorts");
package floatsTest := import("tests/floats");
package mathTest := import("tests/math");

type Test := struct {
	a : float32;
	b : string;
	c : int;
	d : bool;
	e : Test;
}
*/

package math := import("math/math");
package test := import("tests/test");
package sys := import("sys");

/**
 * This is a comment
 * Extra line
 */

func main() {
	
	var j := math.Diff(0f, 15f);
	sys.Write(sys.String(j));
	sys.Write("\n");
	test.Assert(j, 15f, 0.01f, "Dif 0 15 failed");
	
	/**
    loopsTest.Test();
    arraysTest.Test();
    variablesTest.Test();
    recursionTest.Test();
    primesTest.Test();
    logicalTest.Test();
    sortsTest.Test();
    floatsTest.Test();
    mathTest.Test();**/

}

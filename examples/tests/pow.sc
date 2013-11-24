/**
 * Package that tests whether the sys.PowX functions are working properly.
 *
 * Copyright (c) Blake Loring 2013
 */

package test := import("test");
package math := import("../math/math");

func Test() {

	//Test positive PowInt
	test.Assert(math.Pow(8, 2), 64, "PowInt fail");
	test.Assert(math.Pow(2, 2), 4, "PowInt fail");
	test.Assert(math.Pow(2, 3), 8, "PowInt fail");
	test.Assert(math.Pow(2, 4), 16, "PowInt fail");
	
	//Test positive PowFloats
	test.Assert(math.Pow(8f, 2f), 64f, 0.01f, "PowFloat fail");
	test.Assert(math.Pow(2f, 2f), 4f, 0.01f, "PowFloat fail");
	test.Assert(math.Pow(2f, 3f), 8f, 0.01f, "PowFloat fail");
	test.Assert(math.Pow(2f, 4f), 16f, 0.01f, "PowFloat fail");
	
	//TODO: Test negative pow & edge cases
}

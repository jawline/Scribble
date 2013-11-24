/**
 * Test the Max and Min math functions
 *
 * Copyright (c) Blake Loring 2013
 */

package math := import("../math/math");
package test := import("test");

func Test() {
	
	test.Assert(math.Max(5, 10), 10, "MaxInt(5,10) failure");
	test.Assert(math.Max(5f, 10f), 10f, 0.01f, "MaxFloat(5,10) failure");
	test.Assert(math.Min(5, 10), 5, "MinInt(5,10) failure");
	test.Assert(math.Min(5f, 10f), 5f, 0.01f, "MinFloat(5,10) failure");
	
		
}

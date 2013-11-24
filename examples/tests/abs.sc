/**
 * Test the Math.AbsInt and Math.AbsFloat functions
 *
 * Copyright (c) Blake Loring 2013
 */

package test := import("test");
package math := import("../math/math");
package sys := import("sys");

func Test() {

	test.Assert(15, math.Abs(-15), "AbsInt failed");
	test.Assert(15f, math.Abs(-15f), 0.01f, "AbsFloat failed");

	test.Assert(15, math.Abs(15), "AbsInt failed");
	test.Assert(15f, math.Abs(15f), 0.01f, "AbsFloat failed");

}
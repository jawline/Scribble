/**
 * Test the Math.AbsInt and Math.AbsFloat functions
 *
 * Copyright (c) Blake Loring 2013
 */

package sys := import("sys");
package test := import("test");
package math := import("../math/math");

func Test() {

 test.Assert(15, math.Abs(15), "AbsInt Positive failed");
 test.Assert(15f, math.Abs(15f), 0.001f, "AbsInt Positive float failed");

 test.Assert(10, math.Abs(10), "AbsInt Positive (2) failed");
 test.Assert(10f, math.Abs(10f), 0.001f, "AbsInt Positive (3) float failed");

 test.Assert(15, math.Abs(-15), "AbsInt failed");
 test.Assert(15f, math.Abs(-15f), 0.001f, "AbsFloat failed");

 test.Assert(15, math.Abs(15), "AbsInt failed");
 test.Assert(15f, math.Abs(15f), 0.001f, "AbsFloat failed");

}

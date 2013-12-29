/**
 * Exp tests
 *
 * Copyright (c) Blake Loring 2013
 */
 
package math := import("../math/math");
package sys := import("sys");
package test := import("test");

func Test() {

 test.Assert(math.Exp(0f), 1f, 0.01f, "Exp(0f) fail");
 test.Assert(math.Exp(1f), 2.71828182846f, 0.01f, "Exp(1f) fail");
 test.Assert(math.Exp(2f), 7.38905609894f, 0.01f, "Exp(2f) fail");
	
}

/**
 * Exp tests
 *
 * Copyright (c) Blake Loring 2015
 */
 
package math := import("../math/math");
package sys := import("sys");
package test := import("test");

func Test() {
  test.Assert(math.Gcd(354, 180), 6, "Expected Gcd(354, 180) to equal 6");
}

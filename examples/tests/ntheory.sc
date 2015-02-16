/**
 * Exp tests
 *
 * Copyright (c) Blake Loring 2015
 */
 
package math    := import("../math/math");
package console := import("console");
package test    := import("test");

func Test() {
 console.Log("Number theory tests");
 test.Assert(math.Gcd(354, 180), 6, "Expected Gcd(354, 180) to equal 6");
}

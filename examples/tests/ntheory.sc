/**
 * Exp tests
 *
 * Copyright (c) Blake Loring 2015
 */
package math    := import("../math/math"),
        console := import("console"),
        test    := import("test");

func Test() {
 console.Log("Number theory tests\n");
 test.Assert(math.Gcd(354, 180), 6, "Expected Gcd(354, 180) to equal 6");
 test.Assert(math.Lcm(48, 180), 720, "Expected Lcm(48, 180) to equal 720");
}

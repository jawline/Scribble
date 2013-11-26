/**
 * Test the Math difference functions
 *
 * Copyright (c) Blake Loring 2013
 */
 
 package math := import("../math/math");
 package test := import("test");
 
 func Test() {
 
 	//Dif tests on integers.
 	test.Assert(math.Diff(0, 15), 15, "Dif 0 15 failed");
 	test.Assert(math.Diff(0, -15), 15, "Dif 0 -15 failed");
 	test.Assert(math.Diff(15, -15), 30, "Dif 15 -15 failed");
	test.Assert(math.Diff(-15, 15), 30, "Dif -15 15 failed");
	test.Assert(math.Diff(-15, -30), 15, "Dif -15 -30 failed");
	test.Assert(math.Diff(-15, -100), 85, "Dif -15 -100 failed");
	
	//Dif tests on floats.
	test.Assert(math.Diff(0f, 15f), 15f, 0.01f, "Dif 0 15 failed");
 	test.Assert(math.Diff(0f, -15f), 15f, 0.01f, "Dif 0 -15 failed");
 	test.Assert(math.Diff(15f, -15f), 30f, 0.01f, "Dif 15 -15 failed");
	test.Assert(math.Diff(-15f, 15f), 30f, 0.01f, "Dif -15 15 failed");
	test.Assert(math.Diff(-15f, -30f), 15f, 0.01f, "Dif -15 -30 failed");
	test.Assert(math.Diff(-15f, -100f), 85f, 0.01f, "Dif -15 -100 failed");
 
 }
package test := import("test");

func Test() {

	test.Assert("Hello" = "Hello", false, "Hello = Hello equality check should be false.");
	
	var k := "Hello";
	var r := "Hello";
	
	test.Assert(k = r, false, "k = r should be false");
	
	r := k;
	
	test.Assert(k = k, true, "k=k should be true");
	test.Assert(r = k, true, "r=k after r := k should be true");


}
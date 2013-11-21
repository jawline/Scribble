package test := import("test");

func Test() {
	
	var j := 0;
	
	test.Assert(j, 0, "J should equal zero");
	
	j := 150;

	test.Assert(j, 150, "J should equal 150");
	
	var r := j;

	test.Assert(r, 150, "R should equal 150");
	test.Assert(j, 150, "J should equal 150");

	r := 15;
	test.Assert(r, 15, "R should equal 15");
	test.Assert(j, 150, "J should equal 150");
}

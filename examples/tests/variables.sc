package test := import("test");

func Test() {
	
 var j := 0;
 test.Assert(j, 0, "J should equal zero");
	
 j := 150;
 test.Assert(j, 150, "J should equal 150");
	
 var r := j;
 test.Assert(r, 150, "R should equal 150");
 test.Assert(j, 150, "J should equal 150");

 r += 45;
 test.Assert(r, 195, "R should equal 195");

 r -= 50;
 test.Assert(r, 145, "R should equal 145");

 r := 15;
 test.Assert(r, 15, "R should equal 15");
 test.Assert(j, 150, "J should equal 150");

 test.Assert(r++, 15, "R should equal 15");
}

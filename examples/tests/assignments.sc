/**
 * This package provides function to test assignment operators in Scribble
 *
 * Copyright (c) Blake Loring 2013 - 2015
 */

package test := import("test");

func Test() {

 var q := 0;
 test.Assert(q, 0, "q should equal 0");

 q += 5;
 test.Assert(q, 5, "q should equal 5");

 q -= 5;
 test.Assert(q, 0, "q should equal 0");

 q += 1;
 q := q * 100;
 test.Assert(q, 100, "q should equal 100");

 test.Assert(true, true, "true true fail so false many fail");
 test.Assert(false, false, "so fail many false");
}

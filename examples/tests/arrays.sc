/**
 * This package contains functions to test arrays functionality
 *
 * Copyright (c) Blake Loring 2013
 */

package test := import("test");

func Test() {

 var arr := [150]int;
	
 for var i := 0; i < len(arr); i++ do {
  arr[i] := i;
  test.Assert(arr[i], i, "arr[i] != i fail");
 }

 for i := 0; i < 150; i++ do {
  test.Assert(arr[i], i, "arr[i] != i second loop fail");
 }

}

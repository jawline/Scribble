/**
 * This package provides function to test the logical operators in Scribble
 *
 * Copyright (c) Blake Loring 2013
 */

package test := import("test");

func Test() {
	
	if false or false then {
		test.Fatal("false false or fail so false many fail");
	}
	
	if false or true then {
		
	} else {
		test.Fatal("false true fail so false many fail");
	}
	
	if true or false then {
		
	} else {
		test.Fatal("true false fail so false many fail");
	}
	
	if true or true then {
		
	} else {
		test.Fatal("true true fail so false many fail");
	}
	
	if true and true then {
	} else {
		test.Fatal("true true and fail so false many fail");
	}
	
	if true and false then {
		test.Fatal("true false and fail so false many fail");
	}
	
	if false and true then {
		test.Fatal("false true and fail so false many fail");
	}
	
	if false and false then {
		test.Fatal("false false and fail so false many fail");
	}

}
/**
 *
 *
 * Copyright (c) Blake Loring 2013
 */

import("test");

type TestStructure := struct {
	Hello : int
	World : string
}

func Test() {
	
	var j := TestStructure { 15, "John A Penis" };
	
	test.Assert(j->Hello, 15, "Test structure initialization error");

	j->Hello := j->Hello + 5;
	
	test.Assert(j->Hello, 20, "Test structure get and assign error");
}

/**
 * Test package tests the structure functionality of Scribble.
 *
 * Copyright (c) Blake Loring 2013
 */

package sys := import("sys");
package test := import("test");
package other_struct := import("other_struct");

type TestStructure := struct {
 Hello : int,
 World : int
}

func Test() {

 //Test a structure from this package
 var k := TestStructure { 15, 30 };

 var x := k->Hello;
 test.Assert(x, 15, "Structure initialization on 15 construct incorrect");

 test.Assert(k->Hello, 15, "Structure initialization on 30 construct incorrect");
 test.Assert(k->World, 30, "Structure initialization on 30 construct incorrect");
 
 //Test a structure from another package
 var q := other_struct.TestStructure { 50, 30f, "Hello World", false };

 test.Assert(q->x, 50, "other_struct.TestStructure x");
 test.Assert(q->y, 30f, 0.1f, "other_struct.TestStructure y");
 test.Assert(q->q, false, "other_struct.TestStructure q");

 //Test Q assigns
 q->x := 15;
 q->y := 15f;
 q->q := true;

}

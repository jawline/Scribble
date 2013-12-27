/**
 *
 *
 * Copyright (c) Blake Loring 2013
 */

package sys := import("sys");
package test := import("test");

type TestStructure := struct {
	Hello : int,
	World : int
}

func Test() {

 var k := TestStructure { 15, 30 };

 //var x := k->Hello;
 //test.Assert(k->Hello, 15, "Structure initialization on 15 construct incorrect");

 test.Assert(k->Hello, 15, "Structure initialization on 30 construct incorrect");
 test.Assert(k->World, 30, "Structure initialization on 30 construct incorrect");
 

}

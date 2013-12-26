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
	
 var j := TestStructure { 15, 20 };

 sys.Write( sys.String( j->Hello ) );
 sys.Write("\n");

 sys.Write( sys.String( j->World ) );
 sys.Write("\n");

 test.Assert(j->Hello, 15, "Structure initialization construct incorrect");
 test.Assert(j->World, 20, "Structure initialization construct incorrect");

}

/**
 * Tests the functionality provided by the maths library.
 *
 * Copyright (c) Blake Loring 2013
 */

package pow := import("pow");
package exp := import("exp");
package abs := import("abs");
package max := import("max");
package dif := import("dif");

func Test() {
 pow.Test();
 exp.Test();
 max.Test();
 abs.Test();
 dif.Test();
}
/**
 * Test the not operator
 *
 * Copyright (c) Blake Loring 2013
 */

package test := import("test");

func Test() {

   if !true then {
      test.Fatal("Not tests error");
   }

   if !false then {
   } else {
      test.Fatal("Not tests error");
   }

}
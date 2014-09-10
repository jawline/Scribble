package test := import("test");

func Test() {

   var MAGIC_VALUE := 0.45f;
   var OTHER_MAGIC := 0.22f;
   var THIRD_MAGIC := 5212412996;

   test.Assert(MAGIC_VALUE = 0.45f, "Magic value test 1 failed");
   test.Assert(OTHER_MAGIC = 0.22f, "Magic value test 2 failed");
   test.Assert(THIRD_MAGIC = 5212412996, "Magic value test 3 failed");
}
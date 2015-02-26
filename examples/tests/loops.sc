package sys     := import("sys"),
        console := import("console"),
        test    := import("test");

func ForTest() {
 var iter := 0;
 for var i := 0; i < 100; i++ do {
  for var j := 0; j < 100; j++ do {
   iter++;
  }
 }
 test.Assert(iter, 10000, "Iter is not correct. Loops test has failed on a for loop");
}

func WhileTest() {
 var i := 0;
 var j := 0;
 var iter := 0;
 
 while i < 100 do {
  j := 0;
  while j < 100 do {
   iter++;
   j++;
  }
  i++;
 }
 test.Assert(iter, 10000, "Iter is not correct. Loops test has failed on a while loop");
}

func ForBetweenTest() {
 var k := 0;
 for var i between 0 and 1000 do {
  k += 1;
  console.Log(sys.String(i) $ " " $ sys.String(k) $ "\n");
 }
 test.Assert(i, 999, "i is not correct");
 test.Assert(k, 1000, "k is not correct");
}

func Test() {
 WhileTest();
 ForTest();
 ForBetweenTest();
}

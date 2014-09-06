package test := import("test");

func FunctionOne(x:int,y:int):int {
 return 5;
}

func FunctionOne(x:int,y:float32):int {
 test.Assert(x = 5, "FunctionOne assert incorrect x");
 test.Assert(y = 5f, "FunctionOne assert incorrect y");
 return 10;
}

func PassAFunction(numExecutes:int,fn:func(int, float32):int) {

 test.Assert(fn != nil, "Fn should != nil");

 for var i := 0; i < numExecutes; i++ do {
  test.Assert(fn(5, 5f) = 10, "Fn return incorrect in PassAFunction");
 }

}

func Test() {

 var k:func(int,int):int;
 test.Assert(k = nil, true, "k should equal nil");

 k := &FunctionOne(int,int);
 test.Assert(k(5,5) = 5, true, "k(5,5) should equal 5");

 var r := &FunctionOne(int,int);
 test.Assert(k(5,5) = r(5,5), true, "k(5,5) should equal r(5,5) as r := &FunctionOne & k := FunctionOne");

 var other := &FunctionOne(int,float32);

 test.Assert(other != nil, true, "other should != nil");
 test.Assert(other(5, 5.0f) = 10, true, "other(5, 5.0f) should return 10");

 test.Assert((k(5,5) + r(5,5)) = other(5,5.0f), true, "k(5,5) + r(5,5) = other(5,5.0f) should be true");

 PassAFunction(150, &FunctionOne(int,float32));

}
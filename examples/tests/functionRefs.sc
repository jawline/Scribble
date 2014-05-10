package test := import("test");

func FunctionOne(x:int,y:int):int {
 return 5;
}

func FunctionOne(x:int,y:float32):int {
 return 10;
}

func Test() {

 var k : func(int,int):int;
 var r : func(float32,float32):int;

 test.Assert(k = nil, true, "k should equal nil");
 test.Assert(r = nil, true, "r should equal nil");

 k := *FunctionOne(int,int);

}

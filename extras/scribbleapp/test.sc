package console := import("console");
package sys := import("sys");

func test() {
 console.Log("Hello world from Scribble\n");
}

func DoMath() : int {
 var math := 42;

 console.Log("DoMath result in Scribble: ");
 console.Log(sys.String(42));
 console.Log("\n");

 return math;
}

func DoFactorial( n : int ) : int {

 if n < 2 then
  return 1;

 return n * DoFactorial( n - 1 );
}

func DoBool() : bool {
 return false;
}

func DoStringTwo() : string {
 return "String Two";
}

func DoString() : string {
 return "Hello World Scribble String";
}

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

func DoBool() : bool {
 return false;
}

package console := import("console");
package sys := import("sys");

func f(x:int) -> int {
	return 5;
}

func r(x:int)->int = 5*x;

func main() {
   console.Log("Hello World " $ (true ? "True" : "False") $ sys.String(r(5)) $ "\n");
}

package console := import("console"),
		sys := import("sys");
		
func FiveTimes(x:int) -> int = 5*x;

func Five() -> int {
	console.Log("Five\n");
	return 5;
}

func main() {
   console.Log("Hello World " $ (true ? "True" : "False") $ " " $ sys.String(FiveTimes(Five())) $ "\n");
}

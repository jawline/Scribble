package console := import("console"),
		sys := import("sys");

func Five() -> int {
	console.Log("Five\n");
	return 5;
}

func FiveTimes(x:int) -> int = 5*x;
func TenTimes(x:int) -> int = FiveTimes(2*x);

func main() {
   console.Log("Hello World " $ (true ? "True" : "False") $ " " $ sys.String(TenTimes(Five())) $ "\n");
}
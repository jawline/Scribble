package console := import("console"),
		sys := import("sys");

func Five() -> int := 5;
func FiveTimes(x:int) -> int := 5*x;
func TenTimes(x:int) -> int := FiveTimes(2*x);
func Pow(val:int,pow:int) -> int := (pow = 0) ? 1 : val*Pow(val, pow-1);
func Fibs(x:int) -> int := 
	if x = 0 then 0
	 | x = 1 then 1
	 | otherwise Fibs(x-1) + Fibs(x-2);

func main() {
   console.Log("Hello World " $ (true ? "True" : "False") $ " " $ sys.String(TenTimes(Five())) $ "\n");
   console.Log(sys.String(Pow(2,6)) $ "\n");
   console.Log("Fibs: " $ sys.String(Fibs(7)) $ "\n");
}
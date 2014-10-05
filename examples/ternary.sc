package console := import("console"),
		sys := import("sys");

func Five() -> int := 5;
func FiveTimes(x:int) -> int := 5*x;
func TenTimes(x:int) -> int := FiveTimes(2*x);

func Fibs(x:int) -> int := 
	if x = 0 then 0
	 | x = 1 then 1
	 | otherwise Fibs(x-1) + Fibs(x-2);

func Pow(x:int,r:int) -> int :=
	if r = 0 then 1
	| otherwise x * Pow(x, r-1);

func Even(x:int) -> bool :=
	if x = 0 then true
	 | otherwise Odd(x-1);

func Odd(x:int) -> bool :=
    if x = 0 then false
     | otherwise Even(x-1);

func main() {
   console.Log("Hello World " $ (true ? "True" : "False") $ " " $ sys.String(TenTimes(Five())) $ "\n");
   console.Log(sys.String(Pow(2,6)) $ "\n");
   console.Log("Fibs: " $ sys.String(Fibs(7)) $ "\n");
   console.Log("Pow: " $ sys.String(Pow(2, 5)) $ "\n");
   console.Log("Even(5): " $ sys.String(Even(5)) $ "\n");
   console.Log("Even(6): " $ sys.String(Even(6)) $ "\n");
}
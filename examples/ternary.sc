package console := import("console"),
		sys := import("sys"),
		math := import("math/math"),
		sieve := import("math/sieve");

type Tree := struct {
	a:int,
	left:Tree,
	right:Tree
}

func Traverse(x:Tree) -> int :=
	if x = nil then 0
	 | else Traverse(x->left) + x->a + Traverse(x->right);

func Fibs(x:int) -> int := 
	if x = 0 then 0
	 | x = 1 then 1
	 | else Fibs(x-1) + Fibs(x-2);

func Pow(x:int,r:int) -> int :=
	if r = 0 then 1
	| else x * Pow(x, r-1);

func Even(x:int) -> bool :=
	if x = 0 then true
	 | else Odd(x-1);

func Odd(x:int) -> bool :=
    if x = 0 then false
     | else Even(x-1);

func Five() -> int := 5;
func FiveTimes(x:int) -> int := 5 * x;
func TenTimes(x:int) -> int := FiveTimes(2 * x);
func TenTimesFive() -> int := TenTimes(Five());
func Happy() -> string := "Something something daaa dee de de dee";

func SetMode(x:int, r:bool) { 
 wiring.SetMode(x,r);
}

func Write(x:int, r:bool) {
 wiring.Write(x,r);
}

func Read(x:int) -> bool := wiring.Read(x);

func SumEvents(x:int) -> int {

   var i := 0;
   var sum := 0;
	
   for i = 0; i < 1000; i++ do {
      if (math.Mod(i, 3) = 0) or (math.Mod(i, 5) = 0) then sum := sum + i;
   }

   return sum;
}

func main() {

   console.Log("Prime(7):" $ sys.String(math.Prime(7)) $ "\n");
   console.Log("Diff(-7, 10):" $ sys.String(math.Diff(-7,10)) $ "\n");
   console.Log("Hello World " $ (true ? "True" : "False") $ " " $ sys.String(TenTimesFive()) $ "\n");
   console.Log(sys.String(Pow(2,6)) $ "\n");
   console.Log("Fibs: " $ sys.String(Fibs(15)) $ "\n");
   console.Log("Pow: " $ sys.String(Pow(2, 5)) $ "\n");
   console.Log("Even(100): " $ sys.String(Even(100)) $ "\n");
   console.Log("Even(51): " $ sys.String(Even(51)) $ "\n");
   console.Log(Happy() $ "\n");
   console.Log("Tree Traverse: " $ sys.String(Traverse(Tree{5, Tree{5, Tree{10, Tree{50,nil,nil}, Tree{10, nil, nil}}, Tree{10, nil, nil}}, Tree{10, Tree{150, nil, nil}, Tree{150, nil, nil}}})) $ "\n");
}

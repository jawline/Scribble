package console := import("console"),
		sys := import("sys"),
		math := import("math/math");

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

func main() {
   console.Log("Hello World " $ (true ? "True" : "False") $ " " $ sys.String(TenTimesFive()) $ "\n");
   console.Log(sys.String(Pow(2,6)) $ "\n");
   console.Log("Fibs: " $ sys.String(Fibs(15)) $ "\n");
   console.Log("Pow: " $ sys.String(Pow(2, 5)) $ "\n");
   console.Log("Even(100): " $ sys.String(Even(100)) $ "\n");
   console.Log("Even(51): " $ sys.String(Even(51)) $ "\n");
   console.Log(Happy() $ "\n");
   console.Log("Tree Traverse: " $ sys.String(Traverse(Tree{5, Tree{5, Tree{10, Tree{50,nil,nil}, Tree{10, nil, nil}}, Tree{10, nil, nil}}, Tree{10, Tree{150, nil, nil}, Tree{150, nil, nil}}})) $ "\n");
}
package math    := import("math/math"),
        sys     := import("sys"),
        console := import("console");

func fizzOrBuzz(x:int)->string :=
	if math.Mod(x, 15) = 0 then "fizzbuzz"
	|  math.Mod(x, 3)  = 0 then "fizz"
	|  math.Mod(x, 5)  = 0 then "buzz"
	|  else sys.String(x);

func main() {
    for var i := 0; i < 150; i++; {
        console.Log(fizzOrBuzz(i) $ "\n");
    }
}

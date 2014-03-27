//Import the console package allowing us to write to stdout
package console := import("console");

//Import the sys package for the RandomInt function and string casts
package sys := import("sys");

func Even(n : int) : bool {
 return is n=0? true : Odd(n-1);
}

func Odd(n : int) : bool {
 return is n=0? false : Even(n-1);
}

func main() {

 //Generate a number between 0 and 150 to find the sum of
 var random := sys.RandomInt(150);

 //Write a message about odd/even
 console.Log("Checking if " $ sys.String(random) $ " is even\n");
 
 var even := Even(random);

 console.Log("The value is " $ (is even? "even" : "odd") $ "\n");


}

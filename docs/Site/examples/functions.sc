//Import the console package allowing us to write to stdout
package console := import("console");

//Import the sys package for the RandomInt function and string casts
package sys := import("sys");

func Even(n : int) : bool {

 //If n = 0 then it is a base case return true
 if n = 0 then {
  return true;
 }
 
 return Odd(n-1);
}

func Odd(n : int) : bool {

 //If base case then return false
 if n = 0 then {
  return false;
 }
 
 return Even(n-1);
}

func main() {

 //Generate a number between 0 and 150 to find the sum of
 var random := sys.RandomInt(150);

 //Write a message about odd/even
 console.Log("Checking if " $ sys.String(random) $ " is even\n");
 
 var even := Even(random);
 
 if even then {
  console.Log("The value is even\n");
 } else {
  console.Log("The value is odd\n");
 } 

}

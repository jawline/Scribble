//Import the console package allowing us to write to stdout
package console := import("console");

//Import the sys package for the RandomInt function and string casts
package sys := import("sys");

func IfTest() {

 //Generate the random integer value j
 var j := sys.RandomInt(2000);

 if j > 1000 then {
  console.Log("J is > 1000\n");
 } else if j < 1000 then {
  console.Log("J is < 1000\n");
 } else {
  console.Log("J is 1000\n");
 }

}

func ForTest() {

 //Generate a number between 0 and 150 to find the sum of
 var random := sys.RandomInt(150);

 //Write a message about finding the sum
 console.Log("Finding the sum of all values between 0 and " $ sys.String(random) $ "\n");
 
 //Create a sum value to store the result
 var sum := 0;
 
 //Loop i between 0 and random and add i to sum at each iteration
 for var i := 0; i < random; i++ do {
  sum := sum + i;
 }  
 
 //Write the sum to stdout
 console.Log(sys.String(sum) $ "\n");
}

func WhileTest() {

 //Generate the random integer value j
 var j := sys.RandomInt(2000);

 //Initialize the variable i to 100
 var i := 100;

 //Loop while i > 0 print i and then decrement it by 1
 while i > 0 do {
  console.Log(sys.String(i) $ "\n");
  i--;
 }

}

func main() {
 IfTest();
 ForTest();
 WhileTest();
}


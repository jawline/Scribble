//Import the console package allowing us to write to stdout
package console := import("console");

//Import the sys package for the RandomInt function and string casts
package sys := import("sys");

func main() {

 //Write a message about generating the value
 console.Log("Generating a random number between 0 and 1500\n");
 
 //Create a new variable with a random number between 0 and 1500 in it
 var random := sys.RandomInt(1500);
 
 //Write the random number to stdout
 console.Log(sys.String(random));
 console.Log("\n");
}

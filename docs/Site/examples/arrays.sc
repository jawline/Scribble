//Import the console package allowing us to write to stdout
package console := import("console");

//Import the sys package for the RandomInt function and string casts
package sys := import("sys");

func main() {

 //Create an array of 100 integers
 var intArray := [100]int;

 //Initialize the array so that its values range between 0 and len(array)
 for var i := 0; i < len(intArray); i++ do {
  intArray[i] := i;
 }

 //Loop between len(intArray) - 1 and 0 printing out the value at each index.
 for i := len(intArray) - 1; i > -1; i-- do {
  console.Log(sys.String(intArray[i]) $ "\n");
 }

}

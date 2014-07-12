package sys := import("sys");
package console := import("console");

func Tits():int {
 console.Log("Running Tits\n");
}

func main() {
 console.Log("Write some words\n");

 for var i := 0; i < 100; i++ do {
  console.Log("Boilerplate\n");
 }

 console.Log("Clothes kegged in poo\n");


 console.Log("The one of the heafy jaw\n");
 console.Log("I have a big jaw\n");


 if sys.RandomInt(15000) > 150 then {
  console.Log("You aren't a statistical anomoly\n");
 } else console.Log("You are pillockendned smiley face tee tee teeggge\n");

 console.Log("Now that you mention it that was an awful idea\n");
}

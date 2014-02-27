//Import the packages for console and system libraries
package console := import("console");
package sys := import("sys");

type Name := struct {
 first : string,
 last : string
}

//Define the user structure with name, email and age fields
type User := struct {
 name : Name,
 email : string,
 age : int
}

//Define the function PrintUser which writes 
//the users name email address and age to stdout
func PrintUser(user : User) {
 console.Log("Name: " $ user->name->first $ " " $ user->name->last $ "\nEmail: " $ user->email $ "\nAge: " $ sys.String(user->age) $ "\n");
}

func main() {
 
 //Create a user for John Smith aged 32
 var user := User { Name { "Blake", "Loring" }, "js@email.com", 32 };

 //Print the users details to the screen.
 PrintUser(user);

}


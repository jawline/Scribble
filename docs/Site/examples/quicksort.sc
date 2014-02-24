package sys := import("sys");
package console := import("console");

type User := struct {
 name : string,
 email : string,
 age : int
}

/**
 * The function Younger will return true if a user is younger than 
 * another, used by the QuickSort function when comparing users
 */

func Younger( left : User, right : User) : bool {

 if left->age < right->age then {
  return true;
 }

 return false;
}

/**
 * The function Older will return true if a user is older than 
 * another, used by the QuickSort function when comparing users
 */

func Older( left : User, right : User) : bool {

 if left->age > right->age then {
  return true;
 }

 return false;
}

/**
 * The print user function outputs information about a 
 * generated user to the screen
 */

func PrintUser(user : User) {
 console.Log("Name: " $ user->name $ "\nEmail: " $ user->email $ "\nAge: " $ sys.String(user->age) $ "\n");
}

/**
 * This function calls PrintUser for every element of a user array.
 */

func PrintUsers(users : array(User)) {

 for var i := 0; i < len(users); i++ do {
  PrintUser(users[i]);
  console.Log("\n");
 }

}

/**
 * The QuickSort function takes an array and the index of the lowest and 
 * highest element it should sort between and sorts it by moving any value
 * lower than a selected pivot value to the left of it and any higher value 
 * to the right and then repeating for the arrays to the left and right of 
 * the pivot value until the array is sorted.
 */

func QuickSort( n:array(User), low : int, high : int) {

 var i := low;
 var j := high;

 //Take the pivot value to be the value in the middle
 var pivot := n[i];

 while i <= j do {

  while Younger(n[i], pivot) do {
   i++;
  }
  
  while Older(n[j], pivot) do {
   j--;
  }

  // As long as i <= j swap n[i] and n[j] and increment them both
  if i <= j then {
   var temp := n[i];
   n[i] := n[j];
   n[j] := temp;
   
   i++;
   j--;
  }

 }
 
 if low < j then 
 	QuickSort(n, low, j);
 
 if i < high then 
 	QuickSort(n, i, high);
}

func main() {

 //Create an array of 5 user references
 var users := [5]User;
 
 //Create the users instances and assign them to elements of the array
 users[0] := User{"Jil", "jil@email.com", 29 };
 users[1] := User{"Zox", "zox@alien.com", 1500 };
 users[2] := User{"John", "j@email.com", 22 };
 users[3] := User{"Prim", "prim@email.com", 90 };
 users[4] := User{"Jim", "jim@email.com", 30 };
 
 //Print out the list of users before searching
 console.Log("Users before sort: \n\n");
 PrintUsers(users);

 //User the QuickSort defined above to sort the list of users by age
 QuickSort(users, 0, 4);
 
 console.Log("---------------------------------------------\nUsers after sort: \n\n");
 
 //Print out the list of users after sorting
 PrintUsers(users);
}

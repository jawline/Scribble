/**
 * Scribble tests execution file
 * Copyright (c) Blake Loring 2013
 */

package loopsTest := import("tests/loops");
package logicalTest := import("tests/logical");
package variablesTest := import("tests/variables");
package recursionTest := import("tests/recursion");
package arraysTest := import("tests/arrays");
package primesTest := import("tests/primes");
package sortsTest := import("tests/sorts");
package floatsTest := import("tests/floats");
package mathTest := import("tests/math");
package structTest := import("tests/structures");

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
 console.Log("Name: ");
 console.Log(user->name);
 
 console.Log("\nEmail: ");
 console.Log(user->email);
 
 console.Log("\nAge: ");
 console.Log(sys.String(user->age));
 console.Log("\n");
}

/**
 * The QuickSort function takes an array and the index of the lowest and highest element it should sort between
 * and sorts it by moving any value lower than a selected pivot value to the left of it and any higher
 * value to the right and then repeating for the arrays to the left and right of the pivot value until the array is sorted.
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
 var users := [5]User;
 users[0] := User{"Bob", "b@email.com", 29 };
 users[1] := User{"Bob", "b@email.com", 20 };
 users[2] := User{"John", "j@email.com", 22 };
 users[3] := User{"Jim", "jim@email.com", 90 };
 users[4] := User{"Jim", "jim@email.com", 30 };
 
 QuickSort(users, 0, 4);
 
 for var i := 0; i < len(users); i++ do {
 	PrintUser(users[i]);
 }
 
}

/**
 * The main function executes all of the Scribble unit tests.
func main() {

 loopsTest.Test();
 arraysTest.Test();
 variablesTest.Test();
 recursionTest.Test();
 primesTest.Test();
 logicalTest.Test();
 sortsTest.Test();
 floatsTest.Test();
 mathTest.Test();
 structTest.Test();

}

 */

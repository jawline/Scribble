/**
 * This package provides functions to run the sieve of eratosthenes prime number algorithm and return an array of 
 * booleans signalling whether a number is true or false
 *
 * Copyright (c) Blake Loring 2013-2015
 */

func Sieve(n:int) -> array(bool) {
 var results := [n]bool;
 var i := 0;

 for i between 0 and n do {
  results[i] := true;
 }
 
 //Set 0 and 1 to false, the sieve doesn't catch them
 results[0] := false;
 results[1] := false;
 
 for i between 2 and n do {
  for var j := i*i; j < n; j := j + i do {
   results[j] := false;
  }
 }

 return results;
}

/**
 * This package provides functions to run the sieve of Aristophanes prime number algorithm and return an array of 
 * booleans signalling whether a number is true or false
 *
 * Copyright (c) Blake Loring 2013
 */
 
func Sieve(n:int) -> array(bool) {
 var results := [n]bool;
 for var i between 2 and n {
     results[i] := true;
 }
 for i between 2 and n do {
     if results[i] then {
         for var j := i*i; j < n; j := j + i do {
             results[j] := false;
  	 }
     }
 }
 return results;
}

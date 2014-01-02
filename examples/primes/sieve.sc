/**
 * This package provides functions to run the sieve of eratosthenes prime number algorithm and return an array of 
 * booleans signalling whether a number is true or false
 *
 * Copyright (c) Blake Loring 2013
 */

func Sieve(n:int) : array(bool) {

 var results := [n]bool;
 
 for var i := 2; i < n; i++ do {
  results[i] := true;
 }
 
 
 for i := 2; i < n; i++ do {
 
  if results[i] then {

  	for var j := i*i; j < n; j := j + i do {
  		results[j] := false;
  	}

  }
 
 }

 return results;
}

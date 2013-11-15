/**
 * This package provides functions to perform an in place heap sort on a given array of integers
 *
 * Copyright (c) Blake Loring 2013
 */

/**
 * Performs an in place heap sort on an array of integers and returns a reference to the same array.
 */

func Sort( n : array(int) ) : array(int) {

 for var i := len(n)-1; i > 0; i-- do {
 
  for var j := 0; j < i; j++ do {
  
   if n[j] > n[j+1] then {
    
    var t := n[j];
    n[j] := n[j+1];
    n[j+1] := t;
    
   }  
  
  }
 
 } 

 return n;
}
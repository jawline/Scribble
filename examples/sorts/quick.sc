/**
 * Package contains an implementation of the quicksort algorithm on arrays of integers.
 *
 * Copyright (c) Blake Loring
 */

/**
 * Perform a quicksort on a given array of integers between the low and high indexs.
 */

func qs( n:array(int), low : int, high : int) {

 var i := low;
 var j := high;

 //Take the pivot value to be the value in the middle
 var pivot := n[i];

 while i <= j do {

  while n[i] < pivot do {
  	i++;
  }
  
  while n[j] > pivot do {
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
 	qs(n, low, j);
 
 if i < high then 
 	qs(n, i, high);
}

/**
 * Sort a given array of integers using the quicksort algorithm
 */

func Sort(n : array(int)) : array(int) {
	qs(n, 0, len(n) - 1);
	return n;
}

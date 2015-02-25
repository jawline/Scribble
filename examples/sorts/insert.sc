/**
 * This package provides functions which run insertion sort on arrays of integers to sort them.
 *
 * Copyright (c) Blake Loring 2013
 */

/**
 * Sort a given array of integers using an insertion sort algorithm.
 */
func Sort(n:array(int)) -> array(int) {
 
 for var i := 1; i < len(n); i++ do {
 	var k := n[i];
 	for var j := i - 1; j >= 0 and (k < n[j]); j-- do {
 		n[j+1] := n[j];
 	}
 	n[j+1] := k;
 }

 return n;
}

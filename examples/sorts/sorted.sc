/**
 * Package contains functions to test whether arrays of integers are sorted.
 *
 * Copyright (c) Blake Loring 2013
 */

/**
 * IsSorted returns true if the array n passed is a sorted array of integers
 */
func IsSorted(n:array(int))->bool {

	for var i := 1; i < len(n); i++ do {
		if n[i] < n[i-1] then return false;
	}

	return true;
}

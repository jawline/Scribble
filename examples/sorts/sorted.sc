/**
 * Package contains functions to test whether arrays of integers are sorted.
 *
 * Copyright (c) Blake Loring 2013
 */

/**
 * IsSorted returns true if the array n passed is a sorted array of integers
 */
func IsSorted(list:array(int)) -> bool {

	for var i between 0 and len(list) do {
		if list[i] < list[i-1] then return false;
	}

	return true;
}

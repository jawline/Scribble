/**
 * This package provides functions to check whether a given integer is a prime number
 *
 * Copyright (c) Blake Loring 2013
 */

package sys := import("sys");

func IsPrime(n : int)->bool {

	if n < 2 then return false;

	for var i := 2; i < n; i++ do {
		if sys.Mod(n, i) = 0 then return false;
	}

	return true;
}

/**
 * Package provides functions to test prime number functions provided.
 *
 * Copyright (c) Blake Loring 2013
 */

package test := import("test");
package sys := import("sys");
package sieve := import("../primes/sieve");
package isprime := import("../primes/isprime");

func Test() {

	var primesList := sieve.Sieve(150);

	for var i := 0; i < len(primesList); i++ do {
		
		var isPrimeResult := isprime.IsPrime(i);

		test.Assert(isPrimeResult, primesList[i], "IsPrime differs from primelist result");
	}

}

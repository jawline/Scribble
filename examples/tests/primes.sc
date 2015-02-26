/**
 * Package provides functions to test prime number functions provided.
 *
 * Copyright (c) Blake Loring 2013
 */
package test := import("test"),
        sys := import("sys"),
        sieve := import("../primes/sieve"),
        math := import("../math/math");

func Test() {

 var primesList := sieve.Sieve(150);

 for var i between 0 and len(primesList) do {
  var isPrimeResult := math.Prime(i);
  test.Assert(isPrimeResult, primesList[i], "IsPrime differs from primelist result at "
   $ sys.String(i)
   $ " isPrime " 
   $ sys.String(isPrimeResult) 
   $ " primesList " 
   $ sys.String(primesList[i]));
 }

}

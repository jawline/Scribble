package test := import("test");
package sys := import("sys");
package sieve := import("../primes/sieve");
package isprime := import("../primes/isprime");

func Test() {

	var primesList := sieve.Sieve(150);

	for var i := 0; i < len(primesList); i++ do {
		
		var isPrimeResult := isprime.IsPrime(i);
		
		if isPrimeResult != primesList[i] then {

			sys.Write( sys.String(i) );
			sys.Write(" ");
			
			sys.Write( sys.String( isPrimeResult ) );
			sys.Write(" ");
			
			sys.Write( sys.String ( primesList[i] ) );
			sys.Write(" ");
		
			test.Fatal("IsPrime differs from primesList result");

		}
		
	}

}

package sys := import("sys");

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

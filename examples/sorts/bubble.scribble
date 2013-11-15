package sys := import ("sys");

func Sort( n : array(int) ) : array(int) {
 
 var swapped := true;

 for var i := len(n) - 1; (i > 0); i-- do {
 
 	swapped := false;
 
 	for var j := 0; j < i; j++ do {
 	
  		if (n[j]) > (n[j+1]) then {
		    var temp := n[j];
		    n[j] := n[j+1];
		    n[j+1] := temp;
		    swapped := true;
   		}
	}
 }
 
 return n;
}

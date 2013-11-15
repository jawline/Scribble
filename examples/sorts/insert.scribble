func Sort( n : array(int) ) : array(int) {

 //Loop i between 1 and n
 //Set temp to n[i]
 //Loop j between i and 0 while n[j-1] > temp
 //Set n[j] to n[j-1]
 //End loop
 //n[j] := temp
 //End loop

 var i : int;
 var j : int;
 var k : int;
 
 for i := 1; i < len(n); i++ do {
 	k := n[i];
 	
 	for j := i - 1; (j >= 0) and (k < n[j]); j-- do {
 		n[j+1] := n[j];
 	}
 
 	n[j+1] := k;
 }

 return n;
}

package sys := import("sys");
package test := import("test");

func Test() {
	
	var i := 0;
	var j := 0;
	var iter := 0;
	
	for i := 0; i < 100; i++ do {
	
		for j := 0; j < 100; j++ do {
			iter++;
		}
	
	}
	
	if iter != 10000 then {
		
		sys.Write( sys.String(iter) );
		sys.Write("\n");
		
		test.Fatal("Iter is not correct. Loops test has failed on a for loop");
	}
	
	i := 0;
	iter := 0;
	
	while i < 100 do {
		j := 0;
	
		while j < 100 do {
			iter++;
			j++;
		}
		
		i++;
	}
	
	if iter != 10000 then {
		
		sys.Write( sys.String(iter) );
		sys.Write("\n");
		
		test.Fatal("Iter is not correct. Loops test has failed on a while loop");
	}
	
}

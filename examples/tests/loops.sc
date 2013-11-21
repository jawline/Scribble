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

	test.Assert(iter, 10000, "Iter is not correct. Loops test has failed on a for loop");
	
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

	test.Assert(iter, 10000, "Iter is not correct. Loops test has failed on a while loop");
}

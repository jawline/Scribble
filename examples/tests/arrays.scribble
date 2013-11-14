package test := import("test");

func Test() {

	var arr := [150]int;
	
	for var i := 0; i < len(arr); i++ do {
		
		arr[i] := i;
		
		if arr[i] != i then {
			test.Fatal("arr[i] != i fail");
		}
		
	}

	for i := 0; i < 150; i++ do {
		
		if arr[i] != i then {
			test.Fatal("arr[i] != i fail");
		}
		
	}
}

package test := import("test"),
	sys := import("sys");

func floatArgument(f:float32) {
	
 if f != 36.45f then {
  test.Fatal("Float argument fail");
 }
}

func floatReturn() -> float32 {
 return 16.45f;
}

func Test() {

 var testVariable := 50f;

 if testVariable != 50f then 
  test.Fatal("Float assign fail");

 var testVariableTwo := 40f;

 if testVariableTwo != 40f then
  test.Fatal("Float second assign fail");	

 if testVariable < testVariableTwo then
  test.Fatal("Float less than test failed");
		
 floatArgument(36.45f);
	
 if floatReturn() != 16.45f then {
  test.Fatal("Float return fail");
 }
	
}

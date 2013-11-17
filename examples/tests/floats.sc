package test := import("test");
package sys := import("sys");

func Test() {

	var testVariable := 50f;

	if testVariable != 50f then 
		test.Fatal("Float assign fail");

	var testVariableTwo := 40f;

	if testVariableTwo != 40f then
		test.Fatal("Float second assign fail");	

	if testVariable < testVariableTwo then
		test.Fatal("Float less than test failed");
		
	sys.Int(5f);
}

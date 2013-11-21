import("test");

type TestStructure := struct {
	Hello : int
	World : string
}

func Test() {
	
	var j := TestStructure { 15, "John A Penis" };
	
	test.AssertInt(j->Hello, 15, "Test structure initialization error");

	j->Hello := j->Hello + 5;
	
	test.AssertInt(j->Hello, 20, "Test structure get and assign error");
}

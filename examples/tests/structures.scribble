import("test");

type TestStructure := struct {
	Hello : int
	World : string
}

func Test() {
	
	var j := TestStructure { 15, "John A Penis" };
	
	if j->Hello != 15 then {
		test.Fatal("Test structure initialization error");
	}

	j->Hello := j->Hello + 5;
	
	if j->Hello != 20 then {
		test.Fatal("Test structure get and assign error");
	}

}
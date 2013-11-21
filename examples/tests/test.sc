package sys := import("sys");

func Fatal(error : string) {

	sys.Write( "FATAL ERROR HANG: " );
	sys.Write(error);
	sys.Write("\n");

	while true do {
	}

}

func Assert(val : bool, target : bool, error : string) {
	AssertBool(val, target, error);
}

func Assert(val : int, target : int, error : string) {
	AssertInt(val, target, error);
}

func Assert(val : float32, target : float32, drift : float32, error : string) {
	AssertFloat(val, target, drift, error);
}

func AssertBool(val : bool, target : bool, error : string) {

	if val != target then {
		Fatal(error);
	}

}

func AssertInt(val : int, target : int, error : string) {

	if val != target then {
		test.Fatal(error);
	}

}

func AssertFloat(val : float32, target : float32, drift : float32, error : string) {

	if val > (target + drift) then {
		Fatal(error);
	}

	if val < (target - drift) then {
		Fatal(error);
	}

}

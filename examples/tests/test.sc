package sys := import("sys");

func Fatal(error : string) {

	sys.Write( "FATAL ERROR HANG: " );
	sys.Write(error);
	sys.Write("\n");

	while true do {
	}

}
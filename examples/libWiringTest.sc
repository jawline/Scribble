package console := import("console"),
	wiring := import("libWiring");

func main() {
	wiring.Setup();
	wiring.SetMode(0, true);
	wiring.Write(0, true);
}

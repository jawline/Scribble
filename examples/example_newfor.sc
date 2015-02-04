package console := import("console"),
        sys     := import("sys");

func main() {
    for i between sys.Int(0.1f) and sys.Int(4.5f); {
      console.Log(sys.String(i) $ " wow?");
    }
}

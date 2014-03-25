package sys := import("sys");
package console := import("console");

func main() {
 console.Log( is sys.RandomInt(100) > 50? "Yes\n" : "No\n" );
}

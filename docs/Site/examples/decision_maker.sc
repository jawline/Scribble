package sys := import("sys");
package console := import("console");

func main() {

 if sys.RandomInt(100) > 50 then
  console.Log("Go for it!\n");
 else
  console.Log("Don't!\n");

}

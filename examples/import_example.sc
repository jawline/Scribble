package import_example;

package sys := import("sys");
package console := import("console");
package port := import("imports_test/port");

func main() {
	console.Log("Hello thar world\n");
	port.Test();
}

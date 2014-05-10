/**
 * Scribble tests execution file
 * Copyright (c) Blake Loring 2013
 */

package sys := import("sys");
package console := import("console");

func J() : array(int) {
 return [150]int;
}

/**
 * The main function executes all of the Scribble unit tests.
 */
 
func main() {

 console.Log(sys.String(J()[0]));

}

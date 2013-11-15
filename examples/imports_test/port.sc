/**
 * This package provides a Test function for the imports_example file
 *
 * Copyright (c) Blake Loring 2013
 */

package sys := import("sys");

/*
 * This function outputs the string "Hello thar bud\n" to the output stream.
 */

func Test() {
	sys.Write("Hello thar bud\n");
}

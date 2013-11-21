package sys := import("sys");
package test := import("test");

func Test() {

	test.Assert(sys.PowInt(8, 2), 64, "PowInt fail");
	test.Assert(sys.PowInt(2, 2), 4, "PowInt fail");
	test.Assert(sys.PowInt(2, 3), 8, "PowInt fail");
	test.Assert(sys.PowFloat(8f, 2f), 64f, 0.01f, "PowFloat fail");

}

/**
 * Scribble default math library.
 *
 * Copyright (c) Blake Loring 2013
 */
 
package sys := import("sys");
 
func Exp(pow : float32) : float32 {
	var e := 2.71828182846f;
	return PowFloat(e, pow);
}

func PowInt(val : int, pow : int) : int {
	return sys.PowInt(val, pow);
}

func PowFloat(val : float32, pow : float32) : float32 {
	return sys.PowFloat(val, pow);
}
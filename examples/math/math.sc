/**
 * Scribble default math library.
 *
 * Copyright (c) Blake Loring 2013
 */
 
package sys := import("sys");
 
/**
 * For a given variable n return e^n
 */

func Exp(pow : float32) : float32 {

	var e := 2.71828182846f;

	return PowFloat32(e, pow);
}

/**
 * Return x * e^n or x*Exp(n);
 */

func Exp(x : float32, n : float32) : float32 {
	return x * Exp(n);
}

/**
 * Return the maximum of the left or right values
 */

func MaxInt(left : int, right : int) : int {	

	if left > right then {
		return left;
	}
	
	return right;
}

/**
 * Return the minimum of the left or right values
 */

func MinInt(left : int, right : int) : int {

	if left < right then {
		return left;
	}

	return right;
}

/**
 * Return the max of the left or right values
 */

func MaxFloat32(left : float32, right : float32) : float32 {

	if left > right then {
		return left;
	}
	
	return right;
}


/**
 * Return the min of the left or right values
 */

func MinFloat32(left : float32, right : float32) : float32 {

	if left < right then {
		return left;
	}

	return right;
}

/**
 * Return val to the power of pow ( val^pow )
 */

func PowInt(val : int, pow : int) : int {
	return sys.PowInt(val, pow);
}

/**
 * Return val to the power of pow ( val^pow )
 */

func PowFloat32(val : float32, pow : float32) : float32 {
	return sys.PowFloat(val, pow);
}

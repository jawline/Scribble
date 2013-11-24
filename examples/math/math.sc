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

	return Pow(e, pow);
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

func Max(left : int, right : int) : int {	

	if left > right then {
		return left;
	}
	
	return right;
}

/**
 * Return the minimum of the left or right values
 */

func Min(left : int, right : int) : int {

	if left < right then {
		return left;
	}

	return right;
}

/**
 * Return the max of the left or right values
 */

func Max(left : float32, right : float32) : float32 {

	if left > right then {
		return left;
	}
	
	return right;
}


/**
 * Return the min of the left or right values
 */

func Min(left : float32, right : float32) : float32 {

	if left < right then {
		return left;
	}

	return right;
}

/**
 * Return val to the power of pow ( val^pow )
 */

func Pow(val : int, pow : int) : int {
	return sys.PowInt(val, pow);
}

/**
 * Return val to the power of pow ( val^pow )
 */

func Pow(val : float32, pow : float32) : float32 {
	return sys.PowFloat(val, pow);
}

/**
 * Return the remainder of the division of integer val by integer divisor
 */

func Mod(val : int, divisor : int) : int {
	return sys.Mod(val, divisor);
}

/**
 * Return the positive value of a given float.
 */
 
func Abs(val : float32) : float32 {

	if val < 0f then
		return -val;

	return val;
}

/**
 * Return the positive value of a given integer.
 */

func Abs(val : int) : int {

	if val < 0 then
		return -val;

	return val;
}

/**
 * Return the positive difference between two integers.
 */

func Diff(val1 : int, val2 : int) : int {
	return Abs(val1 - val2);
}

/**
 * Return the positive difference between two floating point values.
 */

func Diff(val1 : float32, val2 : float32) : float32 {
	return Abs(val1 - val2);
}
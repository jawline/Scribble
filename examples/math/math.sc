/**
 * Scribble default math library.
 *
 * Copyright (c) Blake Loring 2013
 */
package sys := import("sys");

/**
 * For a given variable n return e^n
 */
func Exp(pow:float32) -> float32 := Pow(2.71828182846f, pow);

/**
 * Return x * e^n or x*Exp(n);
 */
func Exp(x:float32, n:float32) -> float32 := x * Exp(n);

/**
 * Return the maximum of the left or right values
 */
func Max(left:int, right:int) -> int := 
	if left > right then left
	 | else right;

/**
 * Return the minimum of the left or right values
 */
func Min(left:int, right:int) -> int :=
	if left < right then left 
	 | else right;

/**
 * Return the max of the left or right values
 */
func Max(left:float32, right:float32) -> float32 :=
	if left > right then left
	 | else right;

/**
 * Return the min of the left or right values
 */
func Min(left:float32, right:float32) -> float32 :=
	if left < right then left
         | else right;

/**
 * Return val to the power of pow ( val^pow )
 */
func Pow(val:int, pow:int) -> int := sys.PowInt(val, pow);

/**
 * Return val to the power of pow ( val^pow )
 */
func Pow(val:float32, pow:float32) -> float32 := sys.PowFloat(val, pow);

/**
 * Return the remainder of the division of integer val by integer divisor
 */
func Mod(val:int, divisor:int) -> int := sys.Mod(val, divisor);

/**
 * Return the greatest common divisor of two integers
 */
func Gcd(a:int, b:int) -> int :=
 	if b = 0 then a
 	 | else Gcd(b, Mod(a, b));

/**
 * Returns the least common multiple of two numbers
 */
func Lcm(a:int, b:int) -> int := Abs(a*b) / Gcd(a,b);

/**
 * Return the positive value of a given float.
 */
func Abs(val:float32) -> float32 :=
	if val < 0f then -val
	 | else val;

/**
 * Return the positive value of a given integer.
 */
func Abs(val:int) -> int := 
	if val < 0 then -val
	 | else val;

/**
 * Return the positive difference between two integers.
 */
func Diff(val1:int, val2:int) -> int := Abs(val1 - val2);

/**
 * Return the positive difference between two floating point values.
 */
func Diff(val1:float32, val2:float32) -> float32 := Abs(val1 - val2);

/**
 * Return true if the parameter n is a prime number
 */
func Prime(n:int) -> bool {

	if n <= 3 then
		return n > 1;
	
	if sys.Mod(n,2) = 0 or sys.Mod(n, 3) = 0 then
		return false;

	//TODO: Why do I have to bracket (i*i). Sort out left/right association
	for var i := 4; i*i <= n; i++ do {
		if sys.Mod(n, i) = 0 then
			return false;
	}

	return true;
}

/**
 * Returns the value of the fibonacci sequence at a given index
 */
func Fibs(x:int) -> int := 
	if x = 0 then 0
	 | x = 1 then 1
	 | else Fibs(x-1) + Fibs(x-2);

/**
 * Returns true if the given integer is an even number
 */
func Even(x:int) -> bool := Mod(x,2) = 0;

/**
 * Returns true if the given integer is an odd number
 */
func Odd(x:int) -> bool := Mod(x, 2) != 0;

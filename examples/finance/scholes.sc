package CDNF := import("CDNF");

/**
 * Implementation of the Black Scholes formula in Scribble.
 *
 * Copyright (c) Blake Loring 2013
 */

package math := import("../math/math");

func Put(s : float32, x : float32, r : float32, sigma : float32, t : float32) {
 var d1 = (Math.log(S / X) + (r + (Math.pow(sigma, 2) / 2) * T)) / ( sigma * Math.sqrt(T) );
 var d2 = d1 - (sigma * Math.sqrt(T));

		return (X * Math.exp(-r * (T))) * CDNF.CNDF(-d2) - S
				* CDNF.CNDF(-d1);

}

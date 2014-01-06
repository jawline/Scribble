package math := import("../math/math");

/**
 * returns the cumulative normal distribution function (CNDF)
 * for a standard normal: N(0,1)
 * Source:
 * http://stackoverflow.com/questions/442758/which-java-library-computes-the-cumulative-standard-normal-distribution-function
 * http://www.codeproject.com/Messages/2622967/Re-NORMSDIST-function.aspx
 * For use in the CS3930/CS5390 coursework
 *
 * Converted to Scribble by Blake Loring
 */

func CNDF(x : float32) : float32 {
 var neg := 0f;
  
 if x < 0f then {
  neg := 1f;
  x := x * -1f;
 }

 var k := (1f / (1f + 0.2316419f * x));
  
 var y := ((((1.330274429f * k - 1.821255978f) * k + 1.781477937f) * k - 0.356563782f)
				* k + 0.319381530f) * k;

 y := 1.0f - 0.398942280401f * math.Exp(-0.5f * x * x) * y;

 return (1f - neg) * y + neg * (1f - y);
}
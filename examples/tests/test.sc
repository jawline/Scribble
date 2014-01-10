/**
 * Test package provides functions to test values and their expected values and display an error if they are not correct.
 *
 * Copyright (c) Blake Loring 2013
 */

package sys := import("sys");
package console := import("console");

func Fatal(error : string) {

 console.Log( "FATAL ERROR HANG: " );
 console.Log(error);
 console.Log("\n");

 while true do {
 }

}

/**
 * Fatal error if val differs from target
 */

func Assert(val : bool, target : bool, error : string) {
 AssertBool(val, target, error);
}

/**
 * Fatal error if val differs from target
 */

func Assert(val : int, target : int, error : string) {
 AssertInt(val, target, error);
}

/**
 * Fatal error if the value given is more then drift apart from the target value
 */

func Assert(val : float32, target : float32, drift : float32, error : string) {
 AssertFloat(val, target, drift, error);
}

/**
 * Fatal error if val differs from target
 */

func AssertBool(val : bool, target : bool, error : string) {

 if val != target then {	
  console.Log("Assert failed ");
  console.Log( sys.String(val) );
  console.Log(" ");
  console.Log( sys.String(target) );
  console.Log("\n");	
  Fatal(error);
 }

}

/**
 * Fatal error if given value is past target.
 */

func AssertInt(val : int, target : int, error : string) {

 if val != target then {
  console.Log("Assert failed ");
  console.Log( sys.String(val) );
  console.Log(" ");
  console.Log( sys.String(target) );
  console.Log("\n");
  test.Fatal(error);
 }

}

/**
 * Fatal error if the value given is more then drift apart from the target value
 */

func AssertFloat(val : float32, target : float32, drift : float32, error : string) {

 if (val > (target + drift)) or (val < (target - drift)) then {
  console.Log("Assert failed ");
  console.Log( sys.String(val) );
  console.Log(" ");
  console.Log( sys.String(target) );
  console.Log("\n");
  Fatal(error);
 }

}

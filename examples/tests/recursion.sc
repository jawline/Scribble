package test := import("test");

func simple(n:int)->int :=
 if n = 0 then 0
 | else 1 + simple(n-1);

func even(n:int)->bool :=
 if n = 0 then true
 | else odd(n-1);

func odd(n:int)->bool :=
 if n = 0 then false
 | else even(n-1);

func Test() {
 test.Assert(simple(1000), 1000, "Simple(1000) test failed");
 test.Assert(even(1000), true, "Even(1000) test failed");
 test.Assert(odd(1000), false, "Odd(1000) test failed");
}

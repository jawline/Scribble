package sys := import("sys");
package console := import("console");

type Stack := struct {
	payload : int,
	next : Stack
}

func Pop(s : Stack) : Stack {
 if Empty(s) then return nil;
 return s->next;
}

func Push(n : int, s : Stack) : Stack {
 return Stack{n, s};
}

func Top(s : Stack) : int {
 if Empty(s) then return 0;
 return s->payload;
}

func Empty(s : Stack) : bool {
 if s = nil then return true;
 return false;
}

func main() {
 var stack : Stack := Stack{5, Stack { 5, Stack { 20, Stack { 2, nil } } } };
 var ops := Stack{1, Stack { 2, Stack { 3, nil } } };

 while Empty(ops) = false do {
  var f := Top(stack);
  stack := Pop(stack);

  if Empty(stack) then {
   console.Log("Issues bro\n");
  } else {

   var op := Top(ops);
   if op = 1 then f := f + Top(stack);
   else if op = 2 then f := f - Top(stack);
   else if op = 3 then f := f * Top(stack);
   else if op = 4 then f := f / Top(stack);

   stack := Pop(stack);
   stack := Push(f, stack);

   ops := Pop(ops);
  }

 }

 console.Log(sys.String(Top(stack)));
}

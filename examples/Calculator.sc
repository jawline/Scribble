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

func PrintStack(s : Stack) {

 if s = nil then { 
  console.Log("Stack Nil\n");
  return;
 }

 console.Log( sys.String(Top(s)) $ " ");
 
 if s->next != nil then {
  PrintStack(s->next);
 } else {
  console.Log("\n");
 }

}

func main() {

 // The initial stack is the values to be operated on. Each operation will do a thing and then place the result back ont othe stack ( So 5 + 5 + 4 is 5, 5, 4 with 1, 1 as ops
 var stack : Stack := Stack{5, Stack { 5, Stack { 20, Stack { 2, Stack { 4, nil } } } } };

 // The initial ops is the list of operations 1 is add, 2 is sub, 3 is multiply and 4 is divide
 var ops := Stack{1, Stack { 2, Stack { 3, Stack { 4, Stack { 5, nil } } } } };

 sys.Compare("Hello", "Hello");
 console.Log( sys.String( sys.Compare("Hello", "ello") ) );

 //While there are still operations to do
 while Empty(ops) = false do {

  //Get the next op
  var op := Top(ops);
  ops := Pop(ops);

  //Get the first value for the calculations
  var f := Top(stack);
  stack := Pop(stack);
  
  //Do the calculation
  if op = 1 then f := f + Top(stack);
  else if op = 2 then f := f - Top(stack);
  else if op = 3 then f := f * Top(stack);
  else if op = 4 then f := f / Top(stack);
  else if op = 5 then {
   console.Log("Print: " $ sys.String(f) $ "\n");
  }

  //Push the result back onto the stack
  stack := Pop(stack);
  stack := Push(f, stack);
 }

 console.Log("Final stack state: ");
 PrintStack(stack);
}

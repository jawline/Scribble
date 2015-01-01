package test := import("test");
package console := import("console");

type ListNode := struct {
	payload : int,
	next : ListNode
}

func Sum(n : ListNode)->int {
 if n = nil then return 0;
 return Sum(n->next) + n->payload;
}

func Test() {

 //test.Assert(Sum(nil), 0, "Sum of nil should be zero");
 console.Log("TODO: Work out how to handle having function matching and nil\n");
 test.Assert(Sum(ListNode{5, nil}), 5, "Sum of 1 Node of 5 should be 5");
 test.Assert(Sum(ListNode{10, ListNode{5, nil}}), 15, "10 + 5 node");

}

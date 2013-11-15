package test := import("test");
package bubble := import("../sorts/bubble");
package quick := import("../sorts/quick");
package sorted := import("../sorts/sorted");
package heap := import("../sorts/heap");
package insert := import("../sorts/insert");
package populate := import("../sorts/populate");
package sys := import("sys");

func Test() {

	if sorted.IsSorted(bubble.Sort( populate.PopulateWorstCase([100]int) )) = false then {
		populate.PrintList(bubble.Sort( populate.PopulateWorstCase([100]int)));
		test.Fatal("Bubble test sort failed");
	}
	
	if sorted.IsSorted(quick.Sort( populate.PopulateWorstCase([100]int) )) = false then {
		populate.PrintList( quick.Sort( populate.PopulateWorstCase([100]int)));
		test.Fatal("Quick test sort failed");
	}

	if sorted.IsSorted(heap.Sort( populate.PopulateWorstCase([100]int) )) = false then {
		populate.PrintList(heap.Sort( populate.PopulateWorstCase([100]int)));
		test.Fatal("Heap test sort failed");
	}

	if sorted.IsSorted(insert.Sort( populate.PopulateWorstCase([100]int) )) = false then {
		populate.PrintList( insert.Sort( populate.PopulateWorstCase([100]int)));
		test.Fatal("Insert test sort failed");
	}

}

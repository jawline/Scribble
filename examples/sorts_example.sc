package quick := import("sorts/quick");
package populate := import("sorts/populate");
package sys := import("sys");
package console := import("console");

func main() {

	var worstCaseList := populate.PopulateWorstCase([15000]int);

	console.Log("Worst Case: ");
	populate.PrintList(worstCaseList);

	console.Log("\nAfter Sorting: ");
	
	var sortedList := quick.Sort(worstCaseList);
	populate.PrintList(sortedList);

}

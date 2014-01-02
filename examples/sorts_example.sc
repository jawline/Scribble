package quick := import("sorts/quick");
package populate := import("sorts/populate");
package sys := import("sys");

func main() {

	var worstCaseList := populate.PopulateWorstCase([1000]int);

	sys.Log("Worst Case: ");
	populate.PrintList(worstCaseList);

	sys.Log("\nAfter Sorting: ");
	
	var sortedList := quick.Sort(worstCaseList);
	populate.PrintList(sortedList);

}

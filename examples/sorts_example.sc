package quick := import("sorts/quick");
package populate := import("sorts/populate");
package sys := import("sys");

func main() {

	var worstCaseList := populate.PopulateWorstCase([100]int);

	sys.Write("Worst Case: ");
	populate.PrintList(worstCaseList);

	sys.Write("\nAfter Sorting: ");
	
	var sortedList := quick.Sort(worstCaseList);
	populate.PrintList(sortedList);

}

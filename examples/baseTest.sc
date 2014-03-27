type TestStructure := struct {
 Hello : int,
 World : int
}

func main() {

 //Test a structure from this package
 var r := 0;
 var j := 0;
 
 //Test a structure from another package
 var q := TestStructure { 15, 30 };

 q->Hello;
 q->World;

}

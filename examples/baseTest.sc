package console := import("console");

type K := struct{
	x:int,
	k:K
}

type R := struct{
	x:int
}

func main(s:string) {
	console.Log(s);
}

func main() {
	K{5,K{5, nil}};
	main("Done a thing\n");
}

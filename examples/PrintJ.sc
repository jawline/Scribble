package sys := import("sys");
package console := import("console");

type J := struct {
 payload : int,
 next : J
}

func PrintJ(j : J) {
 if j = nil then return;

 console.Log(sys.String(j->payload) $ "\n");
 PrintJ(j->next);
}


func main() {
 PrintJ(J{5, nil});
}

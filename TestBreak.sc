type K := struct {
 x:func(K),
 y:func(K)
}

func A(x:K) {
}

func B():int {
}

func main() {
 K{&A(K), &A(K)};
}

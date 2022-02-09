package main

import . "fmt"

const (
	N   = 10000010
	MOD = 10000007
)

var f [N]int32
var n int

func main() {
	Scan(&n)
	f[1], f[2] = 1, 2
	for i := 3; i <= n; i++ {
		f[i] = (2*f[i-1] + f[i-2]) % MOD
	}
	Print(f[n])
}

/*
0 1 2 3
0 1 3
0 2 1 2 3
0 2 3
0 2 1 3
*/

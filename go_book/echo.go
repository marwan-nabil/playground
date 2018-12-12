package main

import (
	"fmt"
	"os"
	"strings"
)


func main() {
	var s, sep string
	for i := 1; i < len(os.Args); i++ {
		s += sep + os.Args[i]
		sep = " "
	}
	fmt.Println(s)
}


func main() {
	for i, arg := range os.Args[1:] {
		fmt.Print(i)
		fmt.Println(" "+arg)
	}
}


func main(){
	fmt.Println(strings.Join(os.Args, " "))
}

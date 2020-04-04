/* find the sum of even valued fibbonaci numbers, that don't exceed 4 mil. */
#include<stdio.h>
#define LIM 4000000L
// note: the sequence follows this pattern  odd, even, odd, odd, even, odd, odd, even, and so on 
//                                           1    2     3    5    8     13   21   34  55  89  144 
// i want to only generate even fibonnaci numbers.
// assuming that n is an even fibbonaci number, we need to get all fibbonaci nums
// only from fib(n), fib(n+3), fib(n+6), fib(n-3).
// we know: fib(n) = fib(n-1)+fib(n-2)
// also :   fib(n+3) = fib(n+2)+fib(n+1) = fib(n+1)+fib(n)+fib(n)+fib(n-1) = 3fib(n)+2fib(n-1)
//         = 3fib(n)+2[fib(n-2)+fib(n-3)] = 3fib(n)+2fib(n-3)+2[fib(n-3)+fib(n-4)] = 3fib(n)+4fib(n-3)+2[fib(n-4)]
// but  : fib(n-4) = fib(n-5)+fib(n-6) = 2fib(n-6)+fib(n-7)
// so   : fib(n+3)=3fib(n)+4fib(n-3)+4fib(n-6)+2fib(n-7)
// example 144    =3 * 34 +4*8      +4*2      +2*1
// in general (by induction ?) we find
//  fib(n) = 3fib(n-3)+4fib(n-6)+4fib(n-9)+4fib(n-12)+ .... + 4*2 + 2*1
//  fib(n) = 4fib(n-3)+fib(n-6)  
// this can save us the time used in adding odd numbers, provided that the machine does multiplication
// efficiently, i.e. not more costly than addition

int main(){
  long sum =10, fib_n_3=8, fib_n_6=2;

  for(long fib_n=4*fib_n_3+fib_n_6; fib_n<LIM; fib_n = 4*fib_n_3 + fib_n_6){
    sum+=fib_n;
    fib_n_6 = fib_n_3;
    fib_n_3 = fib_n;
  }

  printf("\nThe sum is: %ld\n", sum);
}

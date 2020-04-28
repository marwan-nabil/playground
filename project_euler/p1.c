/* List the sum of all multiples of 3 or 5 under 1000 */
#include<stdio.h>
#define LIM 1000

int main()
{
  // guaranteed method
  long sum=0;
  for(int i =1; i < LIM; i++){
    if(i%3 && i%5)
      ;
    else
      sum+=i;
  }

  printf("\nsum is(straight forward method): %d\n", sum);

  // hopefully efficient method
  sum = 0;
  long m3=3, m5=5, cm=15;
  // calculate sum of common multiples
  while(cm< LIM){
    sum-=cm;
    cm+=15;
  }
  // calculate the sum of multiples of 5
  while(m5 < LIM){
    sum += m5;
    m5+=5;
  }
  // calculate the sum of multiples of 3
  while(m3 < LIM){
    sum += m3;
    m3+=3;
  }
    
  printf("\nsum is(efficient method): %d\n", sum);
  return 0;
}

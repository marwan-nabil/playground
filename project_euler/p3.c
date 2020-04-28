/* The prime factors of 13195 are 5, 7, 13 and 29.
What is the largest prime factor of the number 600851475143 
*/
#include<stdio.h>
#include<stdlib.h>

#define LIM 600851475143L

struct prime {
  long num;
  struct prime *next;
} primes_ll = {2, NULL};

struct prime *last  = &primes_ll;
struct prime *first = &primes_ll;

int is_prime(long num)
{
  struct prime *llptr = first;
  do{
    if(num % (llptr->num))
      llptr = llptr->next ? llptr->next : llptr;
    else
      return 0;
  }
  while(llptr->next);
  return 1;
}

long add_prime()
{
  long num=last->num + 1;
  while(!is_prime(num)){    
    num+=1;
  }
  last->next=(struct prime *) malloc(sizeof(struct prime));
  last = last->next;
  last->next=NULL;
  return last->num=num;  
}

void print_ll()
{
  struct prime *llptr = first;

  while(llptr){
    printf(" %d ", llptr->num);
    llptr=llptr->next;
  }
}

int main()
{
  long factor = first->num;
  struct prime *ptr = first;
  while(ptr){

    ptr=ptr->next;
  }
  
}

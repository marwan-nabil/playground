#include<stdio.h>
#include<stdlib.h>

// a generic doubly linked list element type, X is the element value type
#define ListElement(T) \
  struct {	\
    T val;	\
    void *next;	\
    void *prev;	\
  }
#define element_init(val)
#define LinkedList(T) \
  struct { \
    ListElement(T) first_node; \
    ListElement(T) last_node ; \
    }
#define list_Init(T,PTR)
{
  LinkedList(T) 

}
#define List_insert(VAL,T,LIST) \
  { \
    LIST->

  }


int main(){
  {
    printf("\nHello\n");
    printf("World");
  }
}

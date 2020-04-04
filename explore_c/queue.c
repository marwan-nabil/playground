#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int *array;
	int head;
	int tail;
	unsigned int num_elements;
	unsigned int arr_size;
} Queue;

// main interface to the Queue
// TODO
void enqueue(int item, Queue *qp);
int dequeue(Queue *qp);
// END_TODO
Queue *init_queue(int size);
void destroy_queue(Queue *qp);
void print_queue_nice(Queue *qp);

// Auxiliary functions
void expand_queue(Queue *qp, unsigned int expansion);


int main(){
	printf("Welcome, we will perform some tests on the Queue structure\n"
		   "the queue with all info will be printed after each test.\n");
	Queue *qp;

	// test 1
	qp = init_queue(3);	// allocate a size-3 queue
	enqueue(2, qp); enqueue(3, qp); enqueue(4, qp);	// fill it up
	print_queue_nice(qp);	// print it
	destroy_queue(qp); 	// destroy it

	// test 2
	qp = init_queue(5);	// make another one
	enqueue(2, qp); enqueue(3, qp); enqueue(4, qp);	// fill it
	// ---------------------
	// | 2 | 3 | 4 | ? | ? |
	// ---------------------
	//   ^       ^
	// head		tail
	dequeue(qp); dequeue(qp); dequeue(qp);	// unfill it
	// ---------------------
	// | 2 | 3 | 4 | ? | ? |
	// ---------------------
	// 			 ^   ^
	// 		    tail head
	dequeue(qp); // should fail
	enqueue(1, qp); enqueue(2, qp); enqueue(3, qp); enqueue(4, qp); enqueue(5, qp); // fill it again
	// ---------------------
	// | 3 | 4 | 5 | 1 | 2 |
	// ---------------------
	// 			 ^   ^
	// 		    tail head
	enqueue(6, qp); // should double the queue size and rearrange elements and insert new element
	// -----------------------------------------
	// | 1 | 2 | 3 | 4 | 5 | 6 | ? | ? | ? | ? |
	// -----------------------------------------
	//   ^					 ^
	//	head 				tail
	print_queue_nice(qp);
	destroy_queue(qp);

	// test 3
	qp = init_queue(0); // should work
	enqueue(1, qp);
	print_queue_nice(qp);
	destroy_queue(qp);
	exit(0);
}

Queue *init_queue(int size)
{
	Queue *qp = (Queue *) malloc(sizeof(Queue));
	qp->array = (int *) malloc(size*sizeof(int));
	qp->head = 0U;
	qp->tail = -1;
	qp->num_elements = 0;
	qp->arr_size = size;
	return qp;
}

void destroy_queue(Queue *qp)
{
	free(qp->array);
	free(qp);
}

void print_queue_nice(Queue *qp)
{
	printf("\nQueue stored at address [0x%x] is:\n", qp);
	printf("Meta: head = %d\ttail = %d\tnum_elements = %u\tarr_size = %u\tarray address = 0x%x\n", qp->head, qp->tail, qp->num_elements, qp->arr_size, qp->array);
	printf("Contents:\n");
	// cases:
	// 1- queue is actually empty
	// 2- queue has some elements
	// 		a- elements are well ordered (head < tail)
	//		b- elements are wrapped (tail < head)

	if (qp->num_elements == 0){	// empty queue
		printf("Queue is empty !\n\n");
	} 
	else {	// non-empty queue
		// print top formatting
		for(int i = 0; i < qp->arr_size; i++){
			printf("-----");
		}
		printf("-");
		printf("\n|");

		// print bulk of the queue with formatting
		if (qp->head < qp->tail){	// well ordered
			// print from head to tail
			for(int i = qp->head; i <= qp->tail; i++){
				printf(" %-2d |", qp->array[i]);
			}
			// print the empty queue slots
			for(int i = 0; i < (qp->arr_size - qp->num_elements); i++)
				printf(" ?? |");
		}
		else {	// overlapped
			// print from head to array end
			for(int i = qp->head; i < qp->arr_size; i++)
				printf(" %-2d |", qp->array[i]);
			// print from array start to tail
			for(int i = 0; i <= qp->tail; i++)
				printf(" %-2d |", qp->array[i]);
			// print the empty queue slots
			for(int i = 0; i < (qp->arr_size - qp->num_elements); i++)
				printf(" ?? |");
		}

		// print bottom formatting
		printf("\n");
		for(int i = 0; i < qp->arr_size; i++){
			printf("-----");
		}
		printf("-\n");
	}
}

void expand_queue(Queue *qp, unsigned int expansion)
{
	// make a new queue array with extra extension space
	int *arr = (int *) malloc(qp->arr_size + expansion);

	// copy old array to new bigger array and align well
	// cases:
	// 1- old array is well aligned (head < tail)
	// 2- old array overlaps (tail < head)
	if (qp->head < qp->tail){  // aligned
		for(int i = qp->head, j = 0; i <= qp->tail; i++, j++)
			arr[j] = qp->array[i];
	}
	else {  // overlapped
		int j = 0;
		// copy to the end of the array
		for(int i = qp->head; i < qp->arr_size; i++, j++)
			arr[j] = qp->array[i];
		// copy from start to tail
		for(int i = 0; i <= qp->tail; i++, j++)
			arr[j] = qp->array[i];
	}

	// free the old array
	free(qp->array);

	// modify the qp struct
	qp->array = arr;
	qp->arr_size = (qp->arr_size + expansion);
	qp->head = 0U;
	qp->tail = (unsigned int) (qp->num_elements-1);
}


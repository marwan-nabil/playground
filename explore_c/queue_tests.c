#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int *array;
	int head;
	int tail;
	unsigned int num_elements;
	unsigned int arr_size;
} Queue;


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

int main()
{
	// // test 1
	// Queue q;
	// int arr[6] = {2, 3, 4};
	// q.array = arr;
	// q.head = 0;
	// q.tail = 2;
	// q.num_elements = 3U;
	// q.arr_size = 6U;

	// print_queue_nice(&q);

	// // test 2
	// int arr2[12] = {3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
	// q.array = arr2;
	// q.head = 9;
	// q.tail = 3;
	// q.num_elements = 7U;
	// q.arr_size = 12U;

	// print_queue_nice(&q);

	// // test 3
	// Queue *qp = init_queue(10);
	// qp->array[0] = 0;
	// qp->array[1] = 1;
	// qp->array[2] = 2;
	// qp->array[3] = 3;
	// qp->array[4] = 4;
	// qp->array[5] = 5;

	// qp->head = 0;
	// qp->tail = 5;
	// qp->num_elements = 6;

	// print_queue_nice(qp);

	// // test 4
	// Queue *qp2 = init_queue(19);
	// print_queue_nice(qp2);

	// // test 5
	// Queue *qp = init_queue(6);
	// qp->array[0] = 0;
	// qp->array[1] = 1;
	// qp->array[2] = 2;
	// qp->array[3] = 3;
	// qp->array[4] = 4;
	// qp->array[5] = 5;

	// qp->head = 0;
	// qp->tail = 5;
	// qp->num_elements = 6;

	// print_queue_nice(qp);
	// expand_queue(qp, 4);
	// printf("\nafter expanding the queue by 4 ...\n");
	// print_queue_nice(qp);
}
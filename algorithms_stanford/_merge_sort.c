/* This program implements a simple merge sort operation on an array
NOTE: needs optimizations.
*/
#include <stdio.h>
#include <stdlib.h>

#define MAX_ARR 10

void merge_sort(int *src, int length)
{
	if(length <= 1)
	{
		return;
	}
	// get sub arrays lengths
	int l1 = length/2;
	int l2 = length - l1;
	int temp1[l1];
	int temp2[l2];
	// fill the two sub arrays
	int i, j, k;
	for(i=0; i<l1; i++)
	{
		temp1[i] = src[i];
	}
	for(j=0; i<length; i++, j++)
	{
		temp2[j] = src[i];
	}
	merge_sort(temp1, l1);
	merge_sort(temp2, l2);
	// the two subarrays are now sorted
	i = 0; j = 0; k = 0;
	for(; (j<l1) && (k<l2); i++)
	{
		if(temp1[j] <= temp2[k])
		{
			src[i] = temp1[j++];
		}
		else
		{
			src[i] = temp2[k++];
		}
	}
	if(i<length)
	{
		if(j == l1)
		{
			for(; i < length; i++)
				src[i] = temp2[k++];
		}
		else if(k == l2)
		{
			for(; i<length; i++)
				src[i] = temp1[j++];
		}
	}
	return;
}


void main()
{
	int arr[MAX_ARR];
	for(int i=0; i<MAX_ARR; i++)
	{
		arr[i] = rand()%100;
	}
	
	printf("\nUnsorted elements are:\n");
	for(int i = 0; i<MAX_ARR; i++)
	{
		printf("%d ", arr[i]);
	}
	
	merge_sort(arr, MAX_ARR);
	
	printf("\nSorted elements are:\n");
	for(int i = 0; i<MAX_ARR; i++)
	{
		printf("%d ", arr[i]);
	}
}
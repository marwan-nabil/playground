#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

// 
// general functions
// 

void swap(int *first, int *second)
{
    int temp = *first;
    *first = *second;
    *second = temp;
}

// prints the contents of an array
void print_array(int arr[], int array_size)
{
    for (int i = 0; i < array_size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// prints the contents of an array
void print_array_of_strings(char *arr[], int array_size)
{
    for (int i = 0; i < array_size; i++)
    {
        printf("%s    ", arr[i]);
    }
    printf("\n");
}

// 
// sorting algorithms on arrays
// 

void selection_sort_array(int array[], int array_length)
{
    // a loop on the whole array
    for (int i = 0; i < array_length - 1; i++)
    {
        // initial value of the index
        int index_of_smallest_element = i;

        // a loop on the rest of the array (the still unsorted part)
        for (int j = i + 1; j < array_length; j++)
        {
            if (array[j] < array[index_of_smallest_element])
            {
                index_of_smallest_element = j;
            }
        }

        // swap the minimum element in the sub array with
        // the previous smallest element in it
        swap(&array[index_of_smallest_element], &array[i]);
    }
}

// key = 8
//      { -3  0  1  4  5  6    7   8   11  20  }
// i                                    ^
// j                           ^

void insertion_sort_array(char *array[], int array_length)
{
    int i, j;
    char *key;

    for (i = 1; i < array_length; i++)
    {
        key = array[i];
        j = i - 1;

        // shift elements greater than the key to the right
        while (j >= 0 && strlen(array[j]) > strlen(key))
        {
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = key;
    }
}

// pivot = 4
// array:
// i:
// j:

// used by quick_sort, takes an array and returns a partitioning index, which
// is the place were we need to split the array into two partitions,
// after it runs, all the elements of the first partition are smaller than all the
// elements of the second partition
int partition_array(int arr[], int start_index, int end_index)
{
    int pivot = arr[end_index];
    int i = start_index - 1;

    for (int j = start_index; j <= end_index - 1; j++)
    {
        if (arr[j] < pivot)
        {
            i++;

            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[end_index]);
    return (i + 1);
}

void quick_sort_array(int array[], int start_index, int end_index)
{
    if (start_index < end_index)
    {
        int partitioning_index = partition_array(array, start_index, end_index);

        // sort the 2 sub-arrays
        quick_sort_array(array, start_index, partitioning_index - 1);
        quick_sort_array(array, partitioning_index + 1, end_index);
    }
}


// 
// searching algorithms on arrays
// 

// sequential search
// average case performance:    n^2
int get_index_of_first_occurence_in_array(int array[], int array_length, int value)
{
    for (int i = 0; i < array_length; i++)
    {
        if (array[i] == value)
        {
            return i;
        }
    }
    return -1; // didn't find
}

// sequential search also
int get_index_of_last_occurence_in_array(int array[], int array_length, int value)
{
    for (int i = array_length - 1; i >= 0; i--)
    {
        if (array[i] == value)
        {
            return i;
        }
    }
    return -1; // didn't find
}

// sequential search also
void get_indices_of_any_occurence_in_array(int array[], int array_length, int value, int *number_found, int **found_indices)
{
    int num_indices_found = 0;
    int *indices_array = (int *)malloc(array_length * sizeof(int)); // maximum size for *found_indices array

    for (int i = 0; i < array_length; i++)
    {
        if (array[i] == value)
        {
            indices_array[num_indices_found] = i;
            num_indices_found++;
        }
    }
    // 

    *number_found = num_indices_found;
    *found_indices = indices_array;
}

// binary search
int binary_search_array(int array[], int index_first, int index_last, int value)
{
    if (index_last < index_first)
    {
        // this is a single element not an array
        return -1; // means nothing found
    }

    int index_middle = (index_first + index_last) / 2;

    if (value == array[index_middle])
    {
        return index_middle;
    }

    if (value > array[index_middle])
    {
        // the value is greater than the middle element, so
        // just search the second half of the array
        return binary_search_array(array, (index_middle + 1), index_last, value);
    }
    else
    {
        // the value is less than the middle element, so
        // just search the first half of the array
        return binary_search_array(array, index_first, (index_middle - 1), value);
    }
}
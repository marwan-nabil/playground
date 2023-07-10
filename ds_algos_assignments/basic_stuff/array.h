#pragma once

// general functions
void swap(int *first, int *second);
void print_array(int arr[], int array_size);
void print_array_of_strings(char *arr[], int array_size);

// sorting algorithms for arrays
void selection_sort_array(int array[], int array_length);
void insertion_sort_array(char *array[], int array_length);
void quick_sort_array(int array[], int start_index, int end_index);

// searching algorithms for arrays
int get_index_of_first_occurence_in_array(int array[], int array_length, int value);
int get_index_of_last_occurence_in_array(int array[], int array_length, int value);
void get_indices_of_any_occurence_in_array(int array[], int array_length, int value, int *number_found, int **found_indices);
int binary_search_array(int array[], int index_first, int index_last, int value);

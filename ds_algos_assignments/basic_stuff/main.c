#include <stdio.h>
#include <stdlib.h>

#include "singly_linked_list.h"
#include "doubly_linked_list.h"
#include "array.h"
#include "stack.h"
#include "queue.h"

struct node_sll *get_sll_from_user()
{
    // prepare the list by creating only the first node with default data (0)
    struct node_sll *head = create_new_node_sll(0);

    int input_num; // where the number entered by the user is stored

    // tell the user what to do
    printf("\nplease enter a number to store or any other char to exit: ");

    // read the first data from user
    if (scanf("%d", &input_num) == 1) // scanf() returns the number of integers it has read
    {
        head->data = input_num; // put the number read from user in our first node
    }
    else
    {
        // the user didn't enter a number, exit the program
        exit(1);
    }

    // tell the user to enter more data
    printf("please enter the next number to store or any other char to exit: ");

    // keep reading more data from user and creating new
    // linked list nodes as necessary to hold this data
    while (scanf("%d", &input_num) == 1)
    {
        // scroll through the list to get to the last node
        struct node_sll *current_node = head; // start from the first node
        while (current_node->next)
        {
            current_node = current_node->next;
        }

        // current_node now points to the last node
        // create a new node to store the new value entered by the user
        struct node_sll *new_node = create_new_node_sll(input_num);

        // link the new node to the end of our linked list
        current_node->next = new_node;

        // prompt the user for more input
        printf("please enter the next number to store or any other char to exit: ");
    }
    // the user now has finished inputing numbers
    return head;
}

struct node_dll *get_dll_from_user()
{
    // prepare the list by creating only the first node with default data (0)
    struct node_dll *head = create_new_node_dll(0);

    int input_num; // where the number entered by the user is stored

    // tell the user what to do
    printf("\nplease enter a number to store or any other char to exit: ");

    // read the first data from user
    if (scanf("%d", &input_num) == 1) // scanf() returns the number of integers it has read
    {
        head->data = input_num; // put the number read from user in our first node
    }
    else
    {
        // the user didn't enter a number, exit the program
        exit(1);
    }

    // tell the user to enter more data
    printf("please enter the next number to store or any other char to exit: ");

    // keep reading more data from user and creating new
    // linked list nodes as necessary to hold this data
    while (scanf("%d", &input_num) == 1)
    {
        add_node_at_end_dll(head, input_num);

        // prompt the user for more input
        printf("please enter the next number to store or any other char to exit: ");
    }
    // the user now has finished inputing numbers
    return head;
}

void run_example_1()
{
    printf("\n===== run_example_1() ====\n");

    struct node_sll *head = get_sll_from_user();
    // print all the elements in the linked list
    print_sll_nice(head);
}

void run_example_2()
{
    printf("\n===== run_example_2() ====\n");

    // create a list, by creating just its first node
    struct node_sll *head = create_new_node_sll(0);
    printf("head has value: %p\n", head);

    // fill the list with some random data
    printf("adding some numbers to our list ....\n");
    add_node_at_end_sll(head, 1);
    add_node_at_end_sll(head, 2);
    add_node_at_end_sll(head, 3);
    add_node_at_end_sll(head, 4);
    add_node_at_end_sll(head, 4);
    add_node_at_end_sll(head, 4);
    add_node_at_end_sll(head, 4);
    add_node_at_end_sll(head, 4);
    add_node_at_end_sll(head, 5);
    printf("the list now contains: \n");
    print_sll_nice(head);

    //    head->[0]->[1]->[2]->[3]->[4]->[5]->NULL
    //
    //          [-1]->[0]->[1]->[2]->[3]->[4]->[5]->NULL
    //                 ^
    //          head---|
    //
    // play with the list, adding in the beginning
    printf("adding some numbers to the beginning of our list ....\n");
    add_node_at_beginning_sll(&head, -1); // &head : has the type struct node_sll **
    add_node_at_beginning_sll(&head, -2);
    printf("the list now contains: \n");
    print_sll_nice(head);

    // play with the list, removing elements
    printf("removing nodes that contain 4 and 5 ....\n");
    delete_nodes_that_have_certain_value_sll(&head, 4);
    delete_nodes_that_have_certain_value_sll(&head, 5);
    printf("the list now contains: \n");
    print_sll_nice(head);

    // try to remove the first element of the list (-2)
    printf("removing the first node of the list ....\n");
    delete_nodes_that_have_certain_value_sll(&head, -2);
    printf("the list now contains: \n");
    print_sll_nice(head);
}

void run_example_3()
{
    printf("\n===== run_example_3() ====\n");

    // selection sort
    printf("\n\nselection sort: ");
    int array1[] = {2, 4, 6, 8, 4, 3, 0, -3};
    int array_length = sizeof(array1) / sizeof(int); // how many ints in the array
    printf("\nunsorted array: ");
    print_array(array1, array_length);
    selection_sort_array(array1, array_length);
    printf("sorted array: ");
    print_array(array1, array_length);

    // insertion sort
    printf("\n\ninsertion sort: ");
    char *array2[] = {"marwan", "ahmed", "khaled mohammed", "k", "mm"};
    array_length = sizeof(array2) / sizeof(char *);
    printf("\nunsorted array: ");
    print_array_of_strings(array2, array_length);

    insertion_sort_array(array2, array_length);
    printf("sorted array: ");
    print_array_of_strings(array2, array_length);

    // quick sort
    printf("\n\nquick sort: ");
    int array3[] = {2, 4, 6, 8, 4, 3, -40, 23, 0, -3};
    array_length = sizeof(array3) / sizeof(int); // how many ints in the array
    printf("\nunsorted array: ");
    print_array(array3, array_length);
    quick_sort_array(array3, 0, array_length - 1);
    printf("sorted array: ");
    print_array(array3, array_length);
}

void example_sort_sll()
{
    printf("\n===== example_sort_sll() ====\n");

    struct node_sll *head = get_sll_from_user();

    printf("\n the unsorted list is: ");
    print_sll_nice(head);

    selection_sort_sll(head); // sort the linked list

    printf("\n the sorted list is: ");
    print_sll_nice(head);
}

void example_search_sll()
{
    printf("\n===== example_search_sll() ====\n");

    struct node_sll *head = get_sll_from_user();

    selection_sort_sll(head); // sort the linked list

    struct node_sll *found_node = binary_search_sll(head, 3);
    if (found_node)
    {
        printf("found 3 at this node  [data: %d     next:   %p]\n", found_node->data, found_node->next);
    }
    else
    {
        printf("didn't find any 3 in the provided list\n");
    }
}

void example_search_array()
{
    printf("\n===== example_search_array() ====\n");
    int array1[] = {3, 5, 6, 7, 9, 8, 5, 7, 9, 8, 4, 5, 6};
    int array_length = sizeof(array1) / sizeof(int);

    int *indices_array;
    int found;

    get_indices_of_any_occurence_in_array(array1, array_length, 5, &found, &indices_array);

    printf("number of indices were 5 was found:  %d", found);
    printf("\nthe array of found indices:\n");
    print_array(indices_array, found);

    free(indices_array);
}

void example_sort_dll()
{
    printf("\n===== example_sort_dll() ====\n");

    struct node_dll *head = get_dll_from_user();
    printf("\nthe unsorted dll as given by the user is:\n");
    print_dll(head);

    insertion_sort_dll(&head);
    printf("\nthe sorted dll after the insertion sort is:\n");
    print_dll(head);

}

void example_stack()
{
    printf("\n===== example_stack() ====\n");

    struct stack *stack1 = create_stack(20);
    stack_push(stack1, 888);
    stack_push(stack1, 777);
    stack_push(stack1, 666);
    stack_push(stack1, 555);
    stack_push(stack1, 444);

    printf("\nour stack is now:\n");
    print_stack(stack1);
    
    int just_poped = stack_pop(stack1);
    printf("\njust popped this: %d\n", just_poped);
    just_poped = stack_pop(stack1);
    printf("\njust popped this: %d\n", just_poped);

    printf("\nour stack is now:\n");
    print_stack(stack1);
}

void example_queue()
{
    struct queue *queue1 = create_queue();
    enqueue(queue1, 4);
    enqueue(queue1, 5);
    enqueue(queue1, 6);
    enqueue(queue1, 7);
    enqueue(queue1, 8);

    print_queue(queue1);

    dequeue(queue1);
    dequeue(queue1);
    print_queue(queue1);
}

int main(int argc, char **argv)
{
    // example_search_array();
    // example_search_sll();
    // example_sort_sll();
    // run_example_3();
    // run_example_2();
    // run_example_1();
    // example_sort_dll();
    // example_stack();
    example_queue();
}
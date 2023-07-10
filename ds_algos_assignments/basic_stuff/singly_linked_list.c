#include <stdio.h>
#include <stdlib.h>

#include "singly_linked_list.h"
#include "array.h"  // for swap()

//  print1    O(n)              time taken to execute = (t1) * (number of nodes)
//  print2    O(n*n)            time taken to execute = (t2) * (number of nodes)^2
//  print3    O(n * log(n))
//  print4    O(log(n))

// t2 <<  t1

// this function takes an address to the first node in a linked lists (the head)
// and prints all the list elements until the last node
void print_sll(struct node_sll *head)
{
    struct node_sll *current_node = head; // current_node begins poining at the first node
    int index = 0;

    while (current_node != NULL) // check that the current node we're pointing to exists
    {
        // print the number stored in current_node
        printf("node number %d has value: %d\n", index, current_node->data);
        index++;

        // jump to the next node in the list
        current_node = current_node->next;
    }
    // we've reached the end of the list because current_node now is NULL
}

void print_sll_nice(struct node_sll *head)
{
    struct node_sll *current_node = head; // current_node begins poining at the first node

    printf("head");

    while (current_node != NULL) // check that the current node we're pointing to exists
    {
        printf("-->");
        // print the number stored in current_node
        printf("[%d]", current_node->data);

        // jump to the next node in the list
        current_node = current_node->next;
    }

    printf("-->NULL\n");
}

// calls malloc to allocate a new node and initializes this node
struct node_sll *create_new_node_sll(int data)
{
    struct node_sll *new_node = (struct node_sll *)malloc(sizeof(struct node_sll));

    if(new_node == NULL)
    {
        printf("Error: malloc for new node failed !\n");
        return;
    }

    new_node->data = data;
    new_node->next = NULL; // by default a new node is the last one
    return new_node;
}

// inserts a node at the begining of the linked list
void add_node_at_beginning_sll(struct node_sll **pp_head, int data)
{
    // create a node and fill it with the desired data
    struct node_sll *new_node = create_new_node_sll(data);

    // the new node will be the head node,
    // make it point to the old head node
    new_node->next = *pp_head;

    // make the old head pointer point now to the new head node
    *pp_head = new_node;
}

// inserts a node just after some node in the middle of the list
void add_node_after_this_node_sll(struct node_sll *node_to_insert_after, int data)
{
    // create a new node and fill it with data
    struct node_sll *new_node = create_new_node_sll(data);

    // make the new node point to the node just after node_to_insert_after
    new_node->next = node_to_insert_after->next;

    // make node_to_insert_after point to the new node
    node_to_insert_after->next = new_node;
}

//       O(n)
// inserts a node at the end of the list
void add_node_at_end_sll(struct node_sll *head, int data)
{
    // create the new node and fill it with data
    struct node_sll *new_node = create_new_node_sll(data);

    // start with the head node
    struct node_sll *current_node = head;

    // get to the last node in the list
    while (current_node->next != NULL)
    {
        current_node = current_node->next;
    }
    // now we got to the last node

    // make the (old) last node point to the new node
    current_node->next = new_node;

    return;
}

// void delete_this_node(struct node_sll *this_node, struct node_sll **pp_head)
// {
//     free(node);
// }

void delete_node_after_this_sll(struct node_sll *this_node)
{
    struct node_sll *node_to_delete = this_node->next;
    if (node_to_delete == NULL)
    {
        printf("the node you want to delete doesn't exist");
        return;
    }

    // make the this_node point to one past its next node
    this_node->next = node_to_delete->next;
    free(node_to_delete);
}

void delete_nodes_that_have_certain_value_sll(struct node_sll **pp_head, int value)
{
    // search for the node to be deleted
    struct node_sll *current_node = *pp_head;
    struct node_sll *previous_node = *pp_head;

    while (current_node != NULL)
    {
        // check if this node has the target value to delete or not
        if (current_node->data == value)
        {
            // we found the node that we want to delete

            // now check if this node is the head node or not
            if (current_node == *pp_head)
            {
                // we're actually deleting the first node !
                // change the head pointer to point to our next node
                *pp_head = current_node->next;

                // delete the node
                free(current_node);
            }
            else
            {
                // the node to delete is something other than the first node

                // make the previous node point to the next node
                previous_node->next = current_node->next;

                // delete the node
                free(current_node);
            }
        }

        // update the previous and current node pointers
        previous_node = current_node;
        current_node = current_node->next;
    }
}

void selection_sort_sll(struct node_sll *head)
{
    // current node always points to the first node in the still unsorted sublist
    // initialy, all the list is unsorted, so the unsorted sublist is the whole list
    struct node_sll *current_node = head;

    // loop through the whole list
    while (current_node)
    {
        struct node_sll *smallest_node = current_node;     // initial value for the smallest node found so far
        struct node_sll *target_node = current_node->next; // start sorting from this node

        // loop through the rest of the list (the still unsorted part)
        // and find the smallest node in this part
        while (target_node)
        {
            if ((target_node->data) < (smallest_node->data))
            {
                smallest_node = target_node;
            }

            target_node = target_node->next;
        }

        // swap the smallest node with the first node in
        // the unsorted sublist and continue
        swap(&current_node->data, &smallest_node->data);

        current_node = current_node->next;
    }
}

struct node_sll *find_node_in_sll(struct node_sll *head, int value)
{
    struct node_sll *current_node = head;

    while ((current_node->data != value) && (current_node->next != NULL))
    {
        current_node = current_node->next;
    }

    if (current_node != NULL)
    {
        return current_node;
    }
    else
    {
        return NULL;
    }
}

// function to find out middle element
// this function is private (not declared in the header) because nobody other
// than binary_search_sll() is using it
struct node_sll *find_middle_node_sll(struct node_sll *start, struct node_sll *end)
{
    if (start == NULL)
    {
        return NULL;
    }

    struct node_sll *slow_pointer = start;
    struct node_sll *fast_pointer = start->next;

    while (fast_pointer != end)
    {
        fast_pointer = fast_pointer->next;

        if (fast_pointer != end)
        {
            slow_pointer = slow_pointer->next;
            fast_pointer = fast_pointer->next;
        }
    }

    return slow_pointer;
}

// value = 4
//   4   5   8   9   11  22

// O(nlog(n))
struct node_sll *binary_search_sll(struct node_sll *head, int value)
{
    struct node_sll *first_node = head;
    struct node_sll *last_node = NULL;

    do
    {
        // find the middle node in list
        struct node_sll *middle_node = find_middle_node_sll(first_node, last_node);

        if (middle_node == NULL)
        {
            return NULL;
        }

        if (middle_node->data == value)
        {
            return middle_node;
        }
        else if (middle_node->data < value)
        {
            first_node = middle_node->next;
        }
        else
        {
            last_node = middle_node;
        }
    } while (last_node == NULL || last_node != first_node);

    return NULL;
}

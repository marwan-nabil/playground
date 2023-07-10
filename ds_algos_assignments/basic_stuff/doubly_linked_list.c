#include <stdlib.h>
#include <stdio.h>

#include "doubly_linked_list.h"
#include "array.h" // for swap()

// this function takes an address to the first node in a linked lists (the head)
// and prints all the list elements until the last node
void print_dll(struct node_dll *head)
{
    struct node_dll *current_node = head; // current_node begins poining at the first node
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

// calls malloc to allocate a new node and initializes this node
struct node_dll *create_new_node_dll(int data)
{
    struct node_dll *new_node = (struct node_dll *)malloc(sizeof(struct node_dll));
    new_node->data = data;
    new_node->next = NULL; // by default a new node is the last one
    new_node->prev = NULL; // by default a new node is the first one also
    return new_node;
}

// return a pointer to first node in the list
// given a pointer to any node inside the list
struct node_dll *get_first_node_dll(struct node_dll *any_node)
{
    struct node_dll *current_node = any_node;
    while (current_node->prev != NULL)
    {
        current_node = current_node->prev;
    }
    // here, we guarantee that current_node is the first node in the list
    return current_node;
}

// return a pointer to last node in the list
// given a pointer to any node inside the list
struct node_dll *get_last_node_dll(struct node_dll *any_node)
{
    struct node_dll *current_node = any_node;
    while (current_node->next != NULL)
    {
        current_node = current_node->next;
    }
    // here, we guarantee that current_node is the last node in the list
    return current_node;
}

// inserts a node at the begining of the linked list
// also called "push"
void add_node_at_beginning_dll(struct node_dll **pp_head, int data)
{
    // create a node and fill it with the desired data
    struct node_dll *new_node = create_new_node_dll(data);

    new_node->next = *pp_head;
    (*pp_head)->prev = new_node;
    *pp_head = new_node;
}

// inserts a node at the end of the linked list
// also called "push_back" or "append"
void add_node_at_end_dll(struct node_dll *any_node, int data)
{
    // create a node and fill it with the desired data
    struct node_dll *new_node = create_new_node_dll(data);

    struct node_dll *last_node = get_last_node_dll(any_node);
    last_node->next = new_node;
    new_node->prev = last_node;
}

// inserts a node after the given node
void add_node_after_dll(struct node_dll *current_node, int data)
{
    // create a node and fill it with the desired data
    struct node_dll *new_node = create_new_node_dll(data);

    new_node->next = current_node->next;
    new_node->prev = current_node;
    
    current_node->next = new_node;
    new_node->next->prev = new_node;
}

//        [3]
// [4  8      9   4   5]
// inserts a node before the given node
void add_node_before_dll(struct node_dll *current_node, struct node_dll **pp_head, int data)
{
    // create a node and fill it with the desired data
    struct node_dll *new_node = create_new_node_dll(data);

    if (current_node == *pp_head)
    {
        // the node that we want to insert before is the head node (special case)
        // new_node->prev = current_node->prev;
        new_node->next = current_node;
        current_node->prev = new_node;

        // the head pointer now should point to the new head node
        *pp_head = new_node;
    }
    else
    {
        // any other node
        new_node->prev = current_node->prev;
        new_node->next = current_node;
        current_node->prev = new_node;
    }
}

void delete_node_dll(struct node_dll *node_to_delete, struct node_dll **pp_head)
{
    // check to see if we're about to delete the head node
    if (*pp_head == node_to_delete)
    {
        // move the head pointer to a new position
        *pp_head = node_to_delete->next;
    }
    else
    {
        // we're now sure that there's a node before us
        node_to_delete->prev->next = node_to_delete->next;
    }

    // make sure the node we're about to delete is not the last node
    if (node_to_delete->next != NULL)
    {
        // node_to_delete now has a node before and a node after it
        // we will fix the connection of the node that's after it
        node_to_delete->next->prev = node_to_delete->prev;
    }

    // after we made sure that all connections in the list are valid
    // delete the node
    free(node_to_delete);
}

// linear search
struct node_dll *find_node_in_dll(struct node_dll *head, int value)
{
    struct node_dll *current_node = head;

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

// identical to selection_sort_sll()
void selection_sort_dll(struct node_dll *head)
{
    // current node always points to the first node in the still unsorted sublist
    // initialy, all the list is unsorted, so the unsorted sublist is the whole list
    struct node_dll *current_node = head;

    // loop through the whole list
    while (current_node)
    {
        struct node_dll *smallest_node = current_node;     // initial value for the smallest node found so far
        struct node_dll *target_node = current_node->next; // start sorting from this node

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

// 8 
//                 [-4   5   7   8   9   23]
// current_node:             ^
// private function only used by insertion sort
void insert_node_in_sorted_dll(struct node_dll **pp_head, struct node_dll *node_to_insert)
{
    // check if the always sorted list is empty
    if (*pp_head == NULL)
    {
        *pp_head = node_to_insert;
    }
    // check if the node should be inserted at the beginning
    else if (node_to_insert->data < (*pp_head)->data)
    {
        // put the node in the beginning
        node_to_insert->next = *pp_head;
        (*pp_head)->prev = node_to_insert;
        *pp_head = node_to_insert;
    }
    else
    {
        struct node_dll *current_node = *pp_head;

        // search for a correct position to insert the node
        while ((current_node->next != NULL) && (current_node->next->data < node_to_insert->data))
        {
            current_node = current_node->next;
        }
        // now we should insert the new node just after current_node
        node_to_insert->next = current_node->next;
        // make sure that we're not at the end of the list
        if (current_node->next != NULL)
        {
            // we're in the middle of the list, so node_to_insert->next exists
            current_node->next->prev = node_to_insert;
        }

        current_node->next = node_to_insert;
        node_to_insert->prev = current_node;
        // now, all the links of the new node, and the next and previous nodes are correct
    }
}


//  [6   9]
//                 [7   -4   3     7]
// current_node:    ^
// next_node:       ^

// function to sort a doubly linked list using insertion sort
void insertion_sort_dll(struct node_dll **pp_head)
{
    // make a new dll that is always sorted
    struct node_dll *head_of_sorted_dll = NULL;

    // traverse the given (unsorted) dll, and keep inserting nodes from it
    // to the always sorted dll
    struct node_dll *current_node = *pp_head;
    while (current_node != NULL)
    {
        // save apointer to our next node
        struct node_dll *next_node = current_node->next;

        // take the current node and remove all its links
        // so that it's exactly like a newly created node
        current_node->prev = NULL;
        current_node->next = NULL;

        // insert this node in it's correct position in the "alway sorted" list
        insert_node_in_sorted_dll(&head_of_sorted_dll, current_node);

        current_node = next_node;
    }

    // update the head of the original dll, to now point to the new sorted dll
    *pp_head = head_of_sorted_dll;
}

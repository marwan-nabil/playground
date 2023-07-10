#pragma once

// a node is a single element in the linked list
struct node_sll 
{
    int data; // the actual useful data that we need to store
    struct node_sll *next; // pointer to the next element on the list
};


// general functions
void print_sll(struct node_sll *head);
void print_sll_nice(struct node_sll *head);

// adding and creating nodes
struct node_sll *create_new_node_sll(int data);
void add_node_at_beginning_sll(struct node_sll **pp_head, int data);
void add_node_at_end_sll(struct node_sll *pp_head, int data);
void add_node_after_this_node_sll(struct node_sll *node_to_insert_after, int data);

// deleting nodes
void delete_node_after_this_sll(struct node_sll *this_node);
void delete_nodes_that_have_certain_value_sll(struct node_sll **pp_head, int value);


// sorting algorithms for SLL
void selection_sort_sll(struct node_sll *head);

// searching algorithms for SLL
struct node_sll *find_node_in_sll(struct node_sll *head, int value);
struct node_sll *binary_search_sll(struct node_sll *head, int value);

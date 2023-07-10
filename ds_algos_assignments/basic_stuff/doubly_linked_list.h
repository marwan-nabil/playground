#pragma once

// a node is a single element in the doubly linked list
struct node_dll 
{
    int data; // the actual useful data that we need to store
    struct node_dll *next; // pointer to the next element on the list
    struct node_dll *prev; // pointer to the previous element on the list
};

void print_dll(struct node_dll *head);

// creating and adding nodes
struct node_dll *create_new_node_dll(int data);
void add_node_at_beginning_dll(struct node_dll **pp_head, int data);
void add_node_at_end_dll(struct node_dll *any_node, int data);
void add_node_after_dll(struct node_dll *current_node, int data);
void add_node_before_dll(struct node_dll *current_node, struct node_dll **head, int data);

// deleting nodes
void delete_node_dll(struct node_dll *node_to_delete, struct node_dll **pp_head);

// sorting nodes
void selection_sort_dll(struct node_dll *head);
void insertion_sort_dll(struct node_dll **pp_head);


// searching nodes
struct node_dll *get_first_node_dll(struct node_dll *any_node);
struct node_dll *get_last_node_dll(struct node_dll *any_node);
struct node_dll *find_node_in_dll(struct node_dll *head, int value);


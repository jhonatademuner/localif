#ifndef LIST_H
#define LIST_H

// types
typedef struct list List;
typedef struct list_node ListNode;

// operations

// create empty list
List *create_empty_list();

// add an element at the beginning of the list
void insert_into_the_list(List *l, int **v, int width, int height, char *path, char  *locality);

// recursive function associated with insert_into_the_list
// static void _insert_sorted_into_the_list(List *l, int v);

// // insert an element into the list keeping it sorted
// void insert_sorted_into_the_list(List *l, int v);

// // add an element at the and of the list
// void append_into_the_list(List *l, int v);

// /**
//  * remove a node from list by the its value
//  * mode
//  *   "all": remove all matches
//  *   "first": remove the first match only
//  */
// void remove_from_list(List *l, int val, char mode[]);

// // size of hte list
// int size_list(List *l);

// // check whether an element is in the list
// int is_in_the_list(List *l, int v);

// // check whether the list is empty
// int is_empty(List *l);

// // return a new list with the elements reversed
// // List *reversed_list(List *l);

// // concatenate the lists l1 and l2 (in this order)
// // List *concatenate_lists(List* l1, List *l2);

// // free memory
// void free_list(List *l);

// // free memory
// void free_list(List *l);

// // show all elements of the list
void print_list(List *l);

void extractorsToTxt(List *l);

#endif
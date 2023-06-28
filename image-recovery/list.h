#ifndef LIST_H
#define LIST_H

// types
typedef struct list List;
typedef struct list_node ListNode;

// operations

// create empty list
List *create_empty_list();

// add an element at the beginning of the list
void insert_into_the_list(List *l, int **v, int width, int height, char *path, char *locality);

ListNode *getInfo(List *l, int index);

// // size of hte list
int size_list(List *l);

// show all elements of the list
void print_list(List *l);

void extractorsToTxt(List *l);

void freeListNode(ListNode *node);

void freeList(List *l);

#endif
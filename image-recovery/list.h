#ifndef LIST_H
#define LIST_H

typedef struct list List;
typedef struct list_node ListNode;

List *create_empty_list();

void insert_into_the_list(List *l, int **v, int width, int height, char *path, char *locality);

ListNode *getInfo(List *l, int index);

int size_list(List *l);

void print_list(List *l);

void extractorsToTxt(List *l);

void freeListNode(ListNode *node);

void freeList(List *l);

#endif
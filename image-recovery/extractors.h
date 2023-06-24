#ifndef EXTRACTORS_H
#define EXTRACTORS_H

#include "list.h"

struct list_node;
typedef struct list_node ListNode;

void saveTXT(char *path, int *vector, int size);

void getExtractor(List *l);

int *histogramExtractor(ListNode *l);

#endif
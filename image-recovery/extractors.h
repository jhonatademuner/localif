#ifndef EXTRACTORS_H
#define EXTRACTORS_H

#include "list.h"

struct list_node;
typedef struct list_node ListNode;

void saveTXT(char *path, double *vector, int size, char *type);

void getExtractor(List *l);

int *histogramExtractor(ListNode *l);

void getStatisticalMomentsDescriptors(int **matrix, int width, int height, double vectorSMD[]);

#endif
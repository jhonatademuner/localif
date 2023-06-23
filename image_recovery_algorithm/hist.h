#ifndef HIST_H
#define HIST_H

typedef struct hist Hist;
typedef struct hist_node HistNode;

Hist *create_empty_hist();

void split(char *str, char *descriptorPath, char *locality, char *separator);

void insert_into_the_hist(Hist *h, int v[], char *locality);

void histIterator(char *inputPath, Hist *h);

void getVector(char *filePath, int *vector);

#endif
#ifndef HIST_H
#define HIST_H

typedef struct hist Hist;
typedef struct hist_node HistNode;

Hist *create_empty_hist();

char** splitString(char* str, char separator);

void insert_into_the_hist(Hist *h, int *v, char *locality, char *path);

void histIterator(char *inputPath, Hist *h);

void getVector(char* filePath, int* vector, int vectorSize);

void printHist(Hist *h);

double euclideanDistance(int *vector1, int *vector2, int size);

void calculateDistances(int *userImgVector, Hist *h);

void freeHist(Hist *h);

void sortHist(HistNode *first, HistNode *last);

#endif
#ifndef UTILS_H
#define UTILS_H

char *slice(char *str, size_t start, size_t end);

void listIterator(char *basePath, List *l);

void calcMean(int **matrix, int width, int height, double *mean);

void calcStandardDeviation(int **matrix, int width, int height, double *standardDeviation, double *mean);

void calcAssimetry(int **matrix, int width, int height, double *assimetry, double *mean, double *standardDeviation);

void calcKurtosis(int **matrix, int width, int height, double *kurtosis, double *mean, double *standardDeviation);

#endif // UTILS_H
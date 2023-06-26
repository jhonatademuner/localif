#ifndef MATRIX_H
#define MATRIX_H

void getDimensions(char *filePath, int *width, int *height);

int **readPgm(char *filePath, int *width, int *height);

void print_matrix(int **matrix, int width, int height);

void matrixToPgm(int **matrix, int width, int height, char *filePath);

void freeMatrix(int **matrix, int height);

#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "matrix.h"

void getDimensions(char *filePath, int *width, int *height)
{
    FILE *file;
    file = fopen(filePath, "rt");

    fscanf(file, "%*s");
    fscanf(file, "%d %d", width, height);

    fclose(file);
}

int **readPgm(char *filePath, int *width, int *height)
{
    getDimensions(filePath, width, height);
    int **matrix;
    int i, j;
    char buffer[150];

    FILE *file;
    file = fopen(filePath, "rt");

    fgets(buffer, 150, file);
    fgets(buffer, 150, file);
    fgets(buffer, 150, file);

    matrix = (int **)malloc(*height * sizeof(int *));
    for (i = 0; i < *height; i++)
    {
        matrix[i] = (int *)malloc(*width * sizeof(int));
    }

    for (i = 0; i < *height; i++)
    {
        for (j = 0; j < *width; j++)
        {
            fscanf(file, "%d", &matrix[i][j]);
        }
    }

    fclose(file);
    return matrix;
}


void matrixToPgm(int **matrix, int width, int height, char *filePath)
{
    char str[100];
    sprintf(str, "%s", filePath);
    FILE *file = fopen(str, "w");

    fprintf(file, "P2\n");
    fprintf(file, "%d %d\n", width, height);
    fprintf(file, "255\n");

    int i, j;
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            fprintf(file, "%d ", matrix[i][j]);
        }
        fprintf(file, "\n");
    }
    fclose(file);
}

void freeMatrix(int **matrix, int height)
{
    int i;
    for (i = 0; i < height; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
}
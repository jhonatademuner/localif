#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "extractors.h"
#include "matrix.h"
#include "list.h"

//@ -----=============================----- @\\
//@ -----========== STRUCTS ==========----- @\\
//@ -----=============================----- @\\

struct list
{
    ListNode *first;
};

struct list_node
{
    int height;
    int width;
    int **info;
    char *path;
    char *locality;
    ListNode *next;
};

//@ -----=============================----- @\\
//@ -----======== OPERATIONS =========----- @\\
//@ -----=============================----- @\\

void saveTXT(char *path, int *vector, int size)
{
    FILE *file = fopen(path, "w");
    int i;
    for (i = 0; i < size; i++)
    {
        fprintf(file, "%d ", vector[i]);
    }
    fclose(file);
}

int *histogramExtractor(ListNode *p)
{
    int *vector = (int *)calloc(256, sizeof(int));
    int i, j;
    for (i = 0; i < p->height; i++)
    {
        for (j = 0; j < p->width; j++)
        {
            vector[p->info[i][j]]++;
        }
    }
    return vector;
}

void getExtractor(List *l)
{
    ListNode *aux = l->first;
    int i = 0;
    FILE *file = fopen("histogram-extractor/index.txt", "w");
    int imgQuantity = size_list(l);
    fprintf(file, "%d\n", imgQuantity);
    while (aux != NULL)
    {
        int *vector = histogramExtractor(aux);
        char *path = (char *)calloc(100, sizeof(char));
        sprintf(path, "histogram-extractor/%s/histogram-extractor-%d.txt", aux->locality, i++);
        saveTXT(path, vector, 256);

        fprintf(file, "%s %s %s\n", aux->path, path, aux->locality);

        aux = aux->next;
    }
    fclose(file);
}

void euclideanDistance(int *vector1, int *vector2, int size)
{
    int i;
    double sum = 0;
    for (i = 0; i < size; i++)
    {
        sum += (vector1[i] - vector2[i]) * (vector1[i] - vector2[i]);
    }
    printf("Distancia euclidiana: %lf\n", sqrt(sum));
}
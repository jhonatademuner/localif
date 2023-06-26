#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "extractors.h"
#include "matrix.h"
#include "list.h"
#include "hist.h"
#include "utils.h"

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

void saveTXT(char *path, double *vector, int size, char *type)
{
    FILE *file = fopen(path, "w");
    for (int i = 0; i < size; i++)
    {
        if(strcmp(type, "int") == 0){
        fprintf(file, "%d ", (int)vector[i]);
        } else {
        fprintf(file, "%lf ", vector[i]);
        }
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

void getStatisticalMomentsDescriptors(int **matrix, int width, int height, double *vectorSMD)
{
    // Inicializacao dos momentos

    double mean[2];
    double standardDeviation[2];
    double assimetry[2];
    double kurtosis[2];

    // Calculo da mean
    calcMean(matrix, width, height, mean);

    // Calculo do standard deviation
    calcStandardDeviation(matrix, width, height, standardDeviation, mean);

    // Calculo da assimetry
    calcAssimetry(matrix, width, height, assimetry, mean, standardDeviation);

    // Calculo da kurtosis
    calcKurtosis(matrix, width, height, kurtosis, mean, standardDeviation);

    // Armazenamento dos momentos no descriptor
    vectorSMD[0] = standardDeviation[0];
    vectorSMD[1] = standardDeviation[1];
    vectorSMD[2] = assimetry[0];
    vectorSMD[3] = assimetry[1];
    vectorSMD[4] = kurtosis[0];
    vectorSMD[5] = kurtosis[1];
}

void getExtractor(List *l)
{
    ListNode *aux = l->first;
    int i = 0;
    FILE *file = fopen("index.txt", "w");
    int imgQuantity = size_list(l);
    fprintf(file, "%d\n", imgQuantity);
    while (aux != NULL)
    {
        int *vector = histogramExtractor(aux);
        double vectorSMD[6];
        getStatisticalMomentsDescriptors(aux->info, aux->width, aux->height, vectorSMD);
        char *path = (char *)calloc(100, sizeof(char));
        char *path2 = (char *)calloc(100, sizeof(char));
        sprintf(path, "histogram-extractor/%s/histogram-extractor-%d.txt", aux->locality, i);
        sprintf(path2, "SMD-extractor/%s/SMD-extractor-%d.txt", aux->locality, i++);
        double doubleVector[256];
        for (int j = 0; j < 256; j++) {
            doubleVector[j] = (double) vector[j];
        }
        saveTXT(path, doubleVector, 256, "int");
        saveTXT(path2, vectorSMD, 6, "double");
        fprintf(file, "%s %s %s %s\n", aux->path, path, path2, aux->locality);

        aux = aux->next;
        free(path);
        free(path2);
    }
    fclose(file);
}

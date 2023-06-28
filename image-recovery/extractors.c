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

// Function to save vector data to a text file
void saveTXT(char *path, double *vector, int size, char *type)
{
    FILE *file = fopen(path, "w");
    for (int i = 0; i < size; i++)
    {
        if (strcmp(type, "int") == 0)
        {
            fprintf(file, "%d ", (int)vector[i]);
        }
        else
        {
            fprintf(file, "%lf ", vector[i]);
        }
    }
    fclose(file);
}

// Function to extract a histogram from a given list node
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

// Function to calculate statistical moments descriptors for a given matrix
void getStatisticalMomentsDescriptors(int **matrix, int width, int height, double *vectorSMD)
{
    // Initialization of moments
    double mean[2];
    double standardDeviation[2];
    double assimetry[2];
    double kurtosis[2];

    // Calculation of mean
    calcMean(matrix, width, height, mean);

    // Calculation of standard deviation
    calcStandardDeviation(matrix, width, height, standardDeviation, mean);

    // Calculation of asymmetry
    calcAssimetry(matrix, width, height, assimetry, mean, standardDeviation);

    // Calculation of kurtosis
    calcKurtosis(matrix, width, height, kurtosis, mean, standardDeviation);

    // Storing the moments in the descriptor
    vectorSMD[0] = standardDeviation[0];
    vectorSMD[1] = standardDeviation[1];
    vectorSMD[2] = assimetry[0];
    vectorSMD[3] = assimetry[1];
    vectorSMD[4] = kurtosis[0];
    vectorSMD[5] = kurtosis[1];
}

// Function to extract features for all images in the list and save them to files
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
        for (int j = 0; j < 256; j++)
        {
            doubleVector[j] = (double)vector[j];
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

#include "hist.h"
#include "matrix.h"
#include "extractors.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//@ -----=============================----- @\\
//@ -----========== STRUCTS ==========----- @\\
//@ -----=============================----- @\\

struct hist
{
    HistNode *first;
};

struct hist_node
{
    int *info;
    char *locality;
    HistNode *next;
};

//@ -----=============================----- @\\
//@ -----======== OPERATIONS =========----- @\\
//@ -----=============================----- @\\

Hist *create_empty_hist()
{
    Hist *h = (Hist *)malloc(sizeof(Hist));
    h->first = NULL;
    return h;
}

void split(char *str, char *descriptorPath, char *locality, char *separator)
{
    int i = 0;
    char *splitedStr;
    splitedStr = strtok(str, separator);
    while (splitedStr != NULL)
    {
        if (i == 1)
        {
            strcpy(descriptorPath, splitedStr);
        }
        else if (i == 2)
        {
            strcpy(locality, splitedStr);
            splitedStr = strtok(NULL, separator);
            return;
        }
        i++;
    }
}

void insert_into_the_hist(Hist *h, int *v, char *locality)
{
    HistNode *node = (HistNode *)malloc(sizeof(HistNode));
    node->info = v;
    node->next = h->first;
    node->locality = locality;
    h->first = node;
};

void getVector(char *filePath, int *vector)
{

    FILE *file = fopen(filePath, "r");
    char *line = fgets(filePath, 700, file);
    int vIndex = 0;
    for (int i = 0; i < strlen(line); i++)
    {
        if (line[i] == ' ')
        {
            char *strNumber;
            int j = i - 1;
            while (line[i] != ' ')
            {
                // strcat(strNumber, line[j])
                printf("%c", line[j]);
                j--;
            }
            vector[vIndex++] = atoi(strNumber);
        }
    }
    fclose(file);
}

void histIterator(char *inputPath, Hist *h)
{
    FILE *file = fopen(inputPath, "r");
    char *cExtractors = fscanf(inputPath, 7, file);
    int nExtractors = atoi(cExtractors);
    printf("%d\n", nExtractors);
    for (int i = 0; i < nExtractors; i++)
    {
        int *vector;
        char *line = fgets(inputPath, 250, file);
        char *locality, *descriptorPath;
        split(line, descriptorPath, locality, " ");
        printf("%s\n", locality);
        printf("%s\n===================\n", descriptorPath);
        // getVector(descriptorPath, vector);
        // printf("%d", vector);
        // insert_into_the_hist(h, vector, locality);
        // free(vector);
    }

    fclose(file);
}
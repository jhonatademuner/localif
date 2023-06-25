#include "hist.h"
#include "matrix.h"
#include "extractors.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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
    char *path;
    double distance;
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

void insert_into_the_hist(Hist *h, int *v, char *locality, char *path)
{
    HistNode *node = (HistNode *)malloc(sizeof(HistNode));
    node->info = malloc(sizeof(int) * 256);
    memcpy(node->info, v, sizeof(int) * 256);
    node->next = h->first;
    node->locality = strdup(locality);
    node->path = strdup(path);
    node->distance;
    h->first = node;
};

char **splitString(char *str, char separator)
{
    char **strings = malloc(strlen(str) * sizeof(char *));
    int stringIndex = 0;
    char *token = strtok(str, &separator);
    while (token != NULL)
    {
        strings[stringIndex] = token;
        stringIndex++;
        token = strtok(NULL, &separator);
    }
    return strings;
}

char *excludeNewline(char *str)
{
    int length = strcspn(str, "\n");
    char *newStr = malloc((length + 1) * sizeof(char));
    strncpy(newStr, str, length);
    newStr[length] = '\0';
    return newStr;
}

void getVector(char *filePath, int *vector, int vectorSize)
{
    FILE *file = fopen(filePath, "r");
    char *line = malloc(2048 * sizeof(char));
    fgets(line, 2048, file);
    fclose(file);

    char *token = strtok(line, " ");
    int index = 0;
    while (token != NULL && index < vectorSize)
    {
        vector[index] = atoi(token);
        index++;
        token = strtok(NULL, " ");
    }

    free(line);
}

void printHist(Hist *h)
{
    HistNode *node = h->first;
    while (node != NULL)
    {
        printf("Vector address: %d\n", &node->info);
        printf("Locality: %s\n", node->locality);
        printf("Path: %s\n", node->path);
        printf("Distance: %lf\n\n", node->distance);
        printf("-----==================================================-----\n\n");
        node = node->next;
    }
}

void histIterator(char *inputPath, Hist *h)
{
    FILE *file = fopen(inputPath, "r");
    char cExtractors[7];
    fgets(cExtractors, 7, file);
    int nExtractors = atoi(cExtractors);
    for (int i = 0; i < nExtractors; i++)
    {
        int vector[256];
        char line[1024];
        char *descriptorPath, *locality, *imgPath;
        char **paths;
        fgets(line, 1024, file);
        paths = splitString(line, ' ');
        imgPath = paths[0];
        descriptorPath = paths[1];
        locality = excludeNewline(paths[2]);
        getVector(descriptorPath, vector, 256);
        insert_into_the_hist(h, vector, locality, imgPath);
    }
    fclose(file);
}

double euclideanDistance(int *vector1, int *vector2, int size)
{
    double sum = 0;
    for (int i = 0; i < size; i++)
    {
        sum += pow((vector1[i] - vector2[i]), 2);
    }
    return sqrt(sum);
}

void calculateDistances(int *userImgVector, Hist *h)
{
    HistNode *node = h->first;
    while (node != NULL)
    {
        node->distance = euclideanDistance(userImgVector, node->info, 256);
        node = node->next;
    }
}

void freeHist(Hist *h)
{
    HistNode *node = h->first;
    while (node != NULL)
    {
        HistNode *aux = node;
        node = node->next;
        free(aux->info);
        free(aux->locality);
        free(aux->path);
        free(aux);
    }
    free(h);
}

void swapNodes(HistNode *node1, HistNode *node2)
{
    int *infoAux = node1->info;
    char *localityAux = node1->locality;
    char *pathAux = node1->path;
    double distanceAux = node1->distance;

    node1->info = node2->info;
    node1->locality = node2->locality;
    node1->path = node2->path;
    node1->distance = node2->distance;

    node2->info = infoAux;
    node2->locality = localityAux;
    node2->path = pathAux;
    node2->distance = distanceAux;
}

void sortHist(Hist *h)
{
    HistNode *node = h->first;
    while (node != NULL)
    {
        HistNode *aux = node->next;
        while (aux != NULL)
        {
            if (node->distance > aux->distance)
            {
                swapNodes(node, aux);
            }
            aux = aux->next;
        }
        node = node->next;
    }
}
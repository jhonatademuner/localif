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
    double *smd;
    char *locality;
    char *path;
    double distance;
    double smdDistance;
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

void insert_into_the_hist(Hist *h, int *v, char *locality, char *path, double *smd)
{
    HistNode *node = (HistNode *)malloc(sizeof(HistNode));
    node->info = malloc(sizeof(int) * 256);
    memcpy(node->info, v, sizeof(int) * 256);
    node->smd = malloc(sizeof(double) * 6);
    memcpy(node->smd, smd, sizeof(double) * 6);
    node->next = h->first;
    node->locality = strdup(locality);
    node->path = strdup(path);
    node->distance;
    node->smdDistance;
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

void getSMDVector(char *filePath, double *vector, int vectorSize)
{
    FILE *file = fopen(filePath, "r");
    char *line = malloc(2048 * sizeof(char));
    fgets(line, 2048, file);
    fclose(file);

    char *token = strtok(line, " ");
    int index = 0;
    while (token != NULL && index < vectorSize)
    {
        vector[index] = atof(token);
        index++;
        token = strtok(NULL, " ");
    }

    free(line);
}

void printHist(Hist *h)
{
    HistNode *node = h->first;
    for (int i = 0; i < 5; i++)
    {
        printf("Locality: %s\n", node->locality);
        printf("Path: %s\n", node->path);
        printf("Vector address: %d\n", &node->info);
        printf("Distance: %lf\n", node->distance);
        printf("SMD address: %d\n", &node->smd);
        printf("SMD Distance: %lf\n\n", node->smdDistance);
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
        double vectorSMD[6];
        char line[1024];
        char *descriptorPath, *locality, *imgPath, *smdPath;
        char **paths;
        fgets(line, 1024, file);
        paths = splitString(line, ' ');
        imgPath = paths[0];
        descriptorPath = paths[1];
        smdPath = paths[2];
        locality = excludeNewline(paths[3]);
        getVector(descriptorPath, vector, 256);
        getSMDVector(smdPath, vectorSMD, 6);
        insert_into_the_hist(h, vector, locality, imgPath, vectorSMD);
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

double euclideanDistanceIndividualSMD(double *vector1, double *vector2, int size)
{
    double distance = 0.0;

    for (int i = 0; i < size; i++)
    {
        double diff = vector1[i] - vector2[i];
        distance += diff * diff;
    }

    distance = sqrt(distance);

    return distance;
}

void calculateDistances(int *userImgVector, double *userSMD, Hist *h)
{
    HistNode *node = h->first;
    while (node != NULL)
    {
        node->distance = euclideanDistance(userImgVector, node->info, 256);
        node->smdDistance = euclideanDistanceIndividualSMD(userSMD, node->smd, 6);
        node = node->next;
    }
}

void freeHistNode(HistNode *node)
{
    free(node->info);
    free(node->smd);
    free(node->locality);
    free(node->path);
    free(node);
}

void freeHist(Hist *h)
{
    HistNode *node = h->first;
    while (node != NULL)
    {
        HistNode *aux = node;
        node = node->next;
        free(aux->info);
        free(aux->smd);
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
    double *smdAux = node1->smd;
    double smdDistanceAux = node1->smdDistance;

    node1->info = node2->info;
    node1->locality = node2->locality;
    node1->path = node2->path;
    node1->distance = node2->distance;
    node1->smd = node2->smd;
    node1->smdDistance = node2->smdDistance;

    node2->info = infoAux;
    node2->locality = localityAux;
    node2->path = pathAux;
    node2->distance = distanceAux;
    node2->smd = smdAux;
    node2->smdDistance = smdDistanceAux;
}

int compareNodes(HistNode *node1, HistNode *node2)
{
    int w1 = 0, w2 = 0;
    int distanceWeight = 6;
    int smdWeight = 3;

    if (node1->distance < node2->distance)
    {
        w2 += distanceWeight;
    }
    else if (node1->distance > node2->distance)
    {
        w1 += distanceWeight;
    }
    if (node1->smdDistance < node2->smdDistance)
    {
        w2 += smdWeight;
    }
    else if (node1->smdDistance > node2->smdDistance)
    {
        w1 += smdWeight;
    }
    if (w1 > w2)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void sortHist(Hist *h)
{
    HistNode *node = h->first;
    HistNode *nextNode;
    int swapped;

    do
    {
        swapped = 0;
        node = h->first;

        while (node->next != NULL)
        {
            nextNode = node->next;

            if (compareNodes(node, nextNode) > 0)
            {
                swapNodes(node, nextNode);
                swapped = 1;
            }

            node = node->next;
        }
    } while (swapped);
}

// function that returns the first 5 localities in the hist, without repetition
void topLocalities(Hist *h, char **rank)
{
    int localityCount[5] = {0, 0, 0, 0, 0};
    char *localities[5] = {NULL, NULL, NULL, NULL, NULL};
    HistNode *node = h->first;
    int i = 0;
    while (node != NULL && i < 5)
    {
        int j;
        for (j = 0; j < i; j++)
        {
            if (strcmp(node->locality, localities[j]) == 0)
            {
                break;
            }
        }
        if (j == i)
        {
            localities[i] = node->locality;
            localityCount[i]++;
            i++;
        }
        node = node->next;
    }
    for (int i = 0; i < 5; i++)
    {
        rank[i] = localities[i];
    }
}

char *getTopLocality(Hist *h)
{
    int localityCount[5] = {0, 0, 0, 0, 0};
    char *localities[5];
    HistNode *node = h->first;
    for (int i = 0; i < 5; i++)
    {
        localities[i] = node->locality;
        localityCount[i]++;
        node = node->next;
    }
    for (int i = 0; i < 5; i++)
    {
        for (int j = i + 1; j < 5; j++)
        {
            if (strcmp(localities[i], localities[j]) == 0)
            {
                localityCount[i]++;
            }
        }
    }
    int max = 0;
    int maxIndex = 0;
    for (int i = 0; i < 5; i++)
    {
        if (localityCount[i] > max)
        {
            max = localityCount[i];
            maxIndex = i;
        }
    }
    return localities[maxIndex];
}

char **rankHist(Hist *h)
{
    char **rank = malloc(5 * sizeof(char *));
    topLocalities(h, rank);
    return rank;
}
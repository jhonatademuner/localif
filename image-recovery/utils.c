#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <math.h>
#include "list.h"
#include "hist.h"
#include "matrix.h"
#include "extractors.h"

//@ -----=============================----- @\\
//@ -----======== OPERATIONS =========----- @\\
//@ -----=============================----- @\\

char *slice(char *str, size_t start, size_t end)
{
    char *result = malloc(end - start + 1);
    strncpy(result, str + start, end - start);
    result[end - start] = '\0';
    return result;
}

void listIterator(char *basePath, List *l)
{
    char path[1000];
    struct dirent *dp;
    DIR *dir = opendir(basePath);

    if (!dir)
        return;

    while ((dp = readdir(dir)) != NULL)
    {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0 && dp->d_type == DT_DIR)
        {
            strcpy(path, basePath);
            strcat(path, "/");
            strcat(path, dp->d_name);

            listIterator(path, l);
        }
        else if (dp->d_type == DT_REG)
        {
            int **matrix;
            int width, height;

            strcpy(path, basePath);
            strcat(path, "/");
            strcat(path, dp->d_name);

            char *locality;

            char *basePathAux = strdup(path);
            locality = slice(basePath, 4, strlen(basePath));

            matrix = readPgm(path, &width, &height);
            insert_into_the_list(l, matrix, width, height, basePathAux, locality);

            listIterator(path, l);
        }
    }

    closedir(dir);
    free(dp);
    free(dir);
}

void calcMean(int **matrix, int width, int height, double *mean)
{
    double meanX = 0.0, meanY = 0.0;
    double countX = 0.0, countY = 0.0;
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            meanX += matrix[i][j];
            countX++;
        }
    }
    
    for (int j = 0; j < width; j++)
    {
        for (int i = 0; i < height; i++)
        {
            meanY += matrix[i][j];
            countY++;
        }
    }
    
    meanX /= countX;
    meanY /= countY;
    
    mean[0] = meanX;
    mean[1] = meanY;
}

void calcStandardDeviation(int **matrix, int width, int height, double *standardDeviation, double *mean)
{   
    double standardDeviationX = 0.0, standardDeviationY = 0.0;
    double countX = 0.0, countY = 0.0;
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            standardDeviationX += pow(matrix[i][j] - mean[0], 2);
            countX++;
        }
    }
    
    for (int j = 0; j < width; j++)
    {
        for (int i = 0; i < height; i++)
        {
            standardDeviationY += pow(matrix[i][j] - mean[1], 2);
            countY++;
        }
    }
    
    standardDeviationX = sqrt(standardDeviationX / countX);
    standardDeviationY = sqrt(standardDeviationY / countY);
    
    standardDeviation[0] = standardDeviationX;
    standardDeviation[1] = standardDeviationY;
}

void calcAssimetry(int **matrix, int width, int height, double *assimetry, double *mean, double *standardDeviation)
{
    double assimetryX = 0.0, assimetryY = 0.0;
    double countX = 0.0, countY = 0.0;
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            assimetryX += pow(matrix[i][j] - mean[0], 3);
            countX++;
        }
    }
    
    for (int j = 0; j < width; j++)
    {
        for (int i = 0; i < height; i++)
        {
            assimetryY += pow(matrix[i][j] - mean[1], 3);
            countY++;
        }
    }
    
    assimetryX /= (countX * pow(standardDeviation[0], 3));
    assimetryY /= (countY * pow(standardDeviation[1], 3));
    
    assimetry[0] = assimetryX;
    assimetry[1] = assimetryY;
}

void calcKurtosis(int **matrix, int width, int height, double *kurtosis, double *mean, double *standardDeviation)
{   
    double kurtosisX = 0.0, kurtosisY = 0.0;
    double countX = 0.0, countY = 0.0;
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            kurtosisX += pow(matrix[i][j] - mean[0], 4);
            countX++;
        }
    }
    
    for (int j = 0; j < width; j++)
    {
        for (int i = 0; i < height; i++)
        {
            kurtosisY += pow(matrix[i][j] - mean[1], 4);
            countY++;
        }
    }
    
    kurtosisX /= (countX * pow(standardDeviation[0], 4));
    kurtosisY /= (countY * pow(standardDeviation[1], 4));
    
    kurtosis[0] = kurtosisX;
    kurtosis[1] = kurtosisY;
}
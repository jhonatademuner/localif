#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
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
}

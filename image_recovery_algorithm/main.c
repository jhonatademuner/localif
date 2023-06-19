#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include "list.h"
#include "matrix.h"
#include "extractors.h"

void slice(const char* str, char* result, size_t start, size_t end)
{
    strncpy(result, str + start, end - start);
}

void listFilesRecursively(char *basePath, List * l)
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

            listFilesRecursively(path, l);
        }
        else if (dp->d_type == DT_REG)
        {
            int ** matrix;
            int width, height;

            // printf("%s/%s\n", basePath, dp->d_name);

            strcpy(path, basePath);
            strcat(path, "/");
            strcat(path, dp->d_name);

            char locality[50] = "";	
            slice(basePath, locality, 4, strlen(basePath));
            printf("%s\n", locality);

            // while (locality != NULL)
            // {
            //     strcpy(locality, strtok(NULL, "/"));
            // }

            matrix = readPgm(path, &width, &height);

            listFilesRecursively(path, l);
        }
    }

    closedir(dir);
}

int main(void)
{

    // struct dirent *entry;
    // DIR *dir, *folder;
    // int **matrix;
    // int width, height;
    List *l;
    l = create_empty_list();

    listFilesRecursively("img", l);

    

    // extractorsToTxt(l);

    // print_list(l);

    return 0;
}

// dir = opendir("img");
// while ((entry = readdir(dir)) != NULL)
// {
//     if (entry->d_type == DT_DIR)
//     {
//         printf("%s\n", entry->d_name);
//         folder = opendir(entry->d_name);
        
//         printf("dwaygdautidwuyawgduywgawyuidgawdygayugdtyaw\n");
//         while((entry = readdir(folder)) != NULL){
//             printf("%s\n", entry->d_name);
//         }
//         closedir(folder);
//         char filePath[150];
//         sprintf(filePath, "img/%s", entry->d_name);
//         matrix = readPgm(filePath, &width, &height);
//         insert_into_the_list(l, matrix, width, height, filePath);
//         printf("matrix: %d\n", matrix);
//     }
// }
// closedir(dir);
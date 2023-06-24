#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include "list.h"
#include "hist.h"
#include "matrix.h"
#include "extractors.h"
#include "utils.h"

//! -----=====================================================----- !\\
//! -----=====================================================----- !\\
//! -----=====================================================----- !\\
//! -----=====================================================----- !\\
//! -----================== LIBERAR MEMORIA ==================----- !\\
//! -----=====================================================----- !\\
//! -----=====================================================----- !\\
//! -----=====================================================----- !\\
//! -----=====================================================----- !\\

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

int main(void)
{

    List *l;
    l = create_empty_list();

    listIterator("img", l);
    getExtractor(l);

    Hist *h;
    h = create_empty_hist();
    histIterator("histogram-extractor/index.txt", h);

//! ============================================================================== !\\
//! ============================================================================== !\\

    List *userList = create_empty_list();
    char userPath[20] = "img-8.pgm";
    int **userMatrix;
    int userWidth, userHeight;
    // printf("dwadawdgahdjga\n");
    userMatrix = readPgm(userPath, &userWidth, &userHeight);
    printf("width = %d\nheight = %d\n", userWidth, userHeight);
    // printf("dwadawdadawdadaw\n");
    insert_into_the_list(userList, userMatrix, userWidth, userHeight, userPath, "user");
    int *userVector = histogramExtractor(userList->first);

//! ============================================================================== !\\
//! ============================================================================== !\\

    
    calculateDistances(userVector, h);
    printHist(h);

    printf("\n\n\n\n\n");

    sortHist(h);



    printHist(h);

    return 0;
};
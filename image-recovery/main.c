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
//! -----================== LIBERAR MEMORIA ==================----- !\\
//! -----=====================================================----- !\\

int main(void)
{
//@ ======================================================================================================================== @\\
//@ ======================================================================================================================== @\\

    List *l;
    l = create_empty_list();
    listIterator("img", l);
    getExtractor(l);

//@ ======================================================================================================================== @\\
//@ ======================================================================================================================== @\\

    Hist *h;
    h = create_empty_hist();
    histIterator("index.txt", h);

//@ ======================================================================================================================== @\\
//@ ======================================================================================================================== @\\

    List *userList;
    int userWidth = 480, userHeight = 800;
    userList = create_empty_list();




    // aqui entra a matriz do usuario
    int **userMatrix;





    insert_into_the_list(userList, userMatrix, userWidth, userHeight, "userPath", "userLocation");
    int *userVector = histogramExtractor(getInfo(userList, 0));
    double userVectorSMD[6];
    getStatisticalMomentsDescriptors(userMatrix, userWidth, userHeight, userVectorSMD);
    calculateDistances(userVector, userVectorSMD, h);
    sortHist(h);

//@ ======================================================================================================================== @\\
//@ ======================================================================================================================== @\\

    char **rankedHist = malloc(5 * sizeof(char *));
    rankedHist = rankHist(h);
    char **result = malloc(6 * sizeof(char *));
    result[0] = getTopLocality(h);
    for (int i = 0; i < 5; i++)
    {
        result[i+1] = rankedHist[i];
    }

    return 0;
}
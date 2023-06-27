#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include "list.h"
#include "hist.h"
#include "matrix.h"
#include "extractors.h"
#include "utils.h"

int main(void)
{
    int choice = -1;

    while (choice != 0)
    {
        printf("Menu:\n");
        printf("1. Load Database\n");
        printf("2. Run User Image PGM\n");
        printf("0. Exit\n");
        printf("Enter your choice (0, 1, or 2): ");
        scanf("%d", &choice);

        if (choice == 1)
        {
            // Load the database
            List *l;
            l = create_empty_list();  // Create an empty list
            listIterator("img", l);  // Iterate through image directory and populate the list
            getExtractor(l);  // Prompt user for feature extraction method

            printf("Database loaded successfully!\n");
        }
        else if (choice == 2)
        {
            // Run user image PGM
            Hist *h;
            h = create_empty_hist();  // Create an empty histogram
            histIterator("index.txt", h);  // Iterate through the index file and populate the histogram

            List *userList = create_empty_list();  // Create an empty list for user's image
            char userPath[20] = "user/img-user.pgm";  // Path to user's image
            int **userMatrix;
            int userWidth, userHeight;
            userMatrix = readPgm(userPath, &userWidth, &userHeight);  // Read user's image and store it in a matrix
            insert_into_the_list(userList, userMatrix, userWidth, userHeight, userPath, "user");  // Insert user's image into the list
            int *userVector = histogramExtractor(getInfo(userList, 0));  // Extract histogram features for user's image
            double userVectorSMD[6];
            getStatisticalMomentsDescriptors(userMatrix, userWidth, userHeight, userVectorSMD);  // Calculate statistical moments descriptors for user's image

            calculateDistances(userVector, userVectorSMD, h);  // Calculate distances between user's image and the database histograms

            sortHist(h);  // Sort the histogram data

            char **rankedHist = malloc(5 * sizeof(char *));
            rankedHist = rankHist(h);  // Rank the histograms based on distances

            printf("First 5 localities:\n");
            for (int i = 0; i < 5; i++)
            {
                printf("%d) %s\n", i + 1, rankedHist[i]);  // Print the ranked localities
            }
            printf("Top locality: %s\n", getTopLocality(h));  // Print the top locality based on rankings
        }
        else if (choice != 0)
        {
            printf("Invalid choice. Please select 0, 1, or 2.\n");
        }
    }

    return 0;
};

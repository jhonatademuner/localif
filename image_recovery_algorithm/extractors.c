#include <stdio.h>
#include <stdlib.h>
#include "extractors.h"
#include "matrix.h"
#include "list.h"

int * histogramExtractor(int ** matrix, int width, int height){
    int *vector = (int *)calloc(256, sizeof(int));
    int i, j;
    for(i = 0; i < height; i++){
        for(j = 0; j < width; j++){
            vector[matrix[i][j]]++;
        }
    }
    return vector;
}

void euclideanDistance(int * vector1, int * vector2, int size){
    int i;
    double sum = 0;
    for(i = 0; i < size; i++){
        sum += (vector1[i] - vector2[i]) * (vector1[i] - vector2[i]);
    }
    printf("%lf\n", sum);
}
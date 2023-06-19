#include "list.h"
#include "matrix.h"
#include "extractors.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// structs -----

struct list {
  ListNode *first;
};

struct list_node {
  int height;
  int width;
  int ** info;
  char *path;
  char *locality;
  ListNode *next;
};

// operations ----

List *create_empty_list() {
  List *l = (List *)malloc(sizeof(List));
  l->first = NULL;
  return l;
}

// int is_empty(List *l) { return l->first == NULL; }

void insert_into_the_list(List *l, int **v, int width, int height, char * path, char * locality) {
  ListNode *node = (ListNode *)malloc(sizeof(ListNode));
  node->info = v;
  node->next = l->first;
  node->height = height;
  node->width = width;
  node->path = path;
  node->locality = locality;
  l->first = node;
}

// void insert_sorted_into_the_list(List *l, int v) {
//   // TO IMPLEMENT
// }

// static void _insert_sorted_into_the_list(List *l, int v) {
//   // TO IMPLEMENT
// }

// int is_in_the_list(List *l, int v) {
//   // TO IMPLEMENT
// }

// static int _is_in_the_list(List *l, int v) {
//   // TO IMPLEMENT
// }

// void remove_from_list(List *l, int val, char mode[]) {
//   // make sure mode is "first" or "all"
//   assert(strcmp(mode, "first") == 0 || strcmp(mode, "all") == 0);

//   ListNode *aux;          // used to remove a record
//   ListNode *p = l->first; // removal pointer
//   ListNode *prev = NULL;  // previous pointer
//   int stop = 0;           // stop flag related to mode

//   // trasverse the list
//   while ((p != NULL) && (!stop)) {
//     // found?
//     if (p->info == val) {
//       // beginning?
//       if (prev == NULL)
//         l->first = p->next;
//       // middle or end?
//       else
//         prev->next = p->next;

//       aux = p;     // store reference of p
//       p = p->next; // update p
//       free(aux);   // release memory

//       // ensure other elements will not be removed
//       if (strcmp(mode, "first") == 0)
//         stop = 1;
//     } else {
//       prev = p;
//       p = p->next;
//     }
//   }
// }

// void free_list(List *l) {
//   ListNode *p = l->first;
//   while (p != NULL) {
//     ListNode *t = p->next; // keep the reference for the next node
//     free(p);               // free the current node
//     p = t;                 // go to the next node
//   }
//   free(l); // free the list structure
// }

// int size_list(List *l) {
//   int cnt = 0;
//   for (ListNode *p = l->first; p != NULL; p = p->next)
//     cnt++;
//   return cnt;
// }

void print_list(List *l) {
  int **matrix;
  int i = 0;
  for (ListNode *p = l->first; p != NULL; p = p->next){
    matrix = p->info;
    printf("matrix %d: %p\n", i++, matrix);
    for (int j = 0; j < p->height; j++){
      for (int k = 0; k < p->width; k++){
        printf("%d ", matrix[j][k]);
      }
      printf("\n");
    }
  }
}

// void histogramToTxt(ListNode *p){
//     char fileName[150];
//     sprintf(fileName, "histogram-extractor/sample%d.txt", i++);
//     FILE *file = fopen(fileName, "w");
//     int *histogram = histogramExtractor(p->info, p->width, p->height);
//     for (int j = 0; j < 256; j++) {
//         fprintf(file, "%d ", histogram[j]);
//     }
//     fclose(file);
// }

// void extractorsToTxt(List *l) {
//     int i = 1;
//     //file foda
//     for (ListNode *p = l->first; p != NULL; p = p->next) {
//       //path da imagem no file foda
//         histogramToTxt(p);
//         //path do extrator criado e colocar no file foda
//         //localidade
//         free(histogram);
//     }
// }
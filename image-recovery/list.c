#include "list.h"
#include "matrix.h"
#include "extractors.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//@ -----=============================----- @\\
//@ -----========== STRUCTS ==========----- @\\
//@ -----=============================----- @\\

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

//@ -----=============================----- @\\
//@ -----======== OPERATIONS =========----- @\\
//@ -----=============================----- @\\

List *create_empty_list()
{
    List *l = (List *)malloc(sizeof(List));
    l->first = NULL;
    return l;
}

void insert_into_the_list(List *l, int **v, int width, int height, char *path, char *locality)
{
    ListNode *node = (ListNode *)malloc(sizeof(ListNode));
    node->info = v;
    node->next = l->first;
    node->height = height;
    node->width = width;
    node->path = path;
    node->locality = locality;
    l->first = node;
}

ListNode *getInfo(List *l, int index)
{
    ListNode *aux = l->first;
    for (int i = 0; i < index; i++)
    {
        aux = aux->next;
    }
    return aux;
}

int size_list(List *l)
{
    int cnt = 0;
    for (ListNode *p = l->first; p != NULL; p = p->next)
        cnt++;
    return cnt;
}

void print_list(List *l)
{
    int **matrix;
    int i = 0;
    for (ListNode *p = l->first; p != NULL; p = p->next)
    {
        matrix = p->info;
        printf("matrix %d: %p\n", i++, matrix);
        printf("path: %s\n", p->path);
        printf("locality: %s\n", p->locality);
        printf("height: %d\n", p->height);
        printf("width: %d\n", p->width);
        printf("=================\n");
    }
}

void freeListNode(ListNode *node)
{
    free(node->info);
    free(node->path);
    free(node->locality);
    free(node);
}

void freeList(List *l)
{
    ListNode *p = l->first;
    while (p != NULL)
    {
        ListNode *aux = p->next;
        freeListNode(p);
        p = aux;
    }
    free(l);
}
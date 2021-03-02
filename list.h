#ifndef QUIZ01_LIST_H
#define QUIZ01_LIST_H

#include <stddef.h>

typedef struct __node {                   
    int value;
    struct __node *next;
} node_t;

void quicksort(node_t **list);

node_t *list_make_node_t(node_t *list, int number);

void list_free(node_t **list);

#endif

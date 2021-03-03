#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

static inline void list_add_node_t(node_t **list, node_t *node_t)
{
    node_t->next = *list;
    *list = node_t;
}

static inline void list_concat(node_t **left, node_t *right)
{
    while (*left)
        left = &((*left)->next);
    *left = right;
}

void list_free(node_t **list)
{
    //    while (list->next) {

    //    }
}

node_t *list_make_node_t(node_t *list, int number)
{
    node_t *node = malloc(sizeof(node_t));

    node->value = number;

    node->next = list;

    return node;
}

void quicksort(node_t **list)
{
    if (!*list)
        return;

#define MAX_LEVELS 300
    void *beg[MAX_LEVELS], *end[MAX_LEVELS];
    beg[0] = *list;
    end[0] = NULL;

    int cur_index = 0;

    do {
        node_t *pivot = (node_t *) beg[cur_index];
        int value = pivot->value;

        // printf("cur_index: %d, pivot value: %d\n", cur_index, value);
        node_t *p = pivot->next;
        pivot->next = NULL;

        node_t *left = NULL, *right = NULL;

        node_t *left_tail = NULL;
        node_t *right_tail = NULL;

        // quick sort in the range
        while (p != end[cur_index]) {
            node_t *n = p;
            p = p->next;

            if (n->value > value) {
                list_add_node_t(&right, n);
                if (right_tail == NULL)
                    right_tail = n;
            } else {
                list_add_node_t(&left, n);
                if (left_tail == NULL)
                    left_tail = n;
            }
        }
        node_t *result = NULL;

        // cut the list to pivot and concat to result
        if (*list != pivot) {
            node_t *list_head = *list;
            while (list_head->next && list_head->next != pivot)
                list_head = list_head->next;
            list_head->next = NULL;
            list_concat(&result, *list);
        }

        list_concat(&result, left);
        list_concat(&result, pivot);
        list_concat(&result, right);

        // concat the rest of the list
        if (p)
            list_concat(&result, p);

        cur_index--;

        if (left && left->next) {
            cur_index++;
            beg[cur_index] = left;
            end[cur_index] = left_tail->next;
        }

        if (right && right->next) {
            cur_index++;
            beg[cur_index] = right;
            end[cur_index] = right_tail->next;
        }

        *list = result;

    } while (cur_index >= 0);
}

#ifndef LAB0_QUEUE_H
#define LAB0_QUEUE_H

/* This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a circular doubly-linked list to represent the set of queue elements
 */

#include <stdbool.h>
#include <stddef.h>

#include "list.h"

/**
 * element_t - Linked list element
 * @value: pointer to array holding string
 * @list: node of a doubly-linked list
 *
 * @value needs to be explicitly allocated and freed
 */
typedef struct {
    int value;
    struct list_head list;
} element_t;

void q_quicksort(struct list_head *head, bool descend);

#endif

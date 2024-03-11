#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

/* Return number of elements in queue */
int q_size(struct list_head *head)
{
    int n = 0;
    struct list_head *node;
    list_for_each (node, head)
        ++n;
    return n;
}

static inline int q_sort_cmp(int *a, int *b, bool descend)
{
    return descend ? *b - *a : *a - *b;
}

void q_quicksort(struct list_head *head, bool descend)
{
    if (!head || list_empty(head) || list_is_singular(head))
        return;

    int i = 0;
    const int n = q_size(head);
    const int max_level = n * 2;
    struct list_head stack[max_level];
    INIT_LIST_HEAD(&stack[0]);

    LIST_HEAD(stack_head);
    LIST_HEAD(left);
    LIST_HEAD(right);
    list_splice_init(head, stack);

    while (i >= 0) {
        list_splice(&stack[i], &stack_head);
        if (!list_empty(&stack_head) && !list_is_singular(&stack_head)) {
            struct list_head *pivot = stack_head.next, *node, *safe;
            int value = list_entry(pivot, element_t, list)->value;
            list_del(pivot);
            list_for_each_safe (node, safe, &stack_head) {
                list_del(node);
                list_add_tail(
                    node, q_sort_cmp(&list_entry(node, element_t, list)->value,
                                     &value, descend) < 0
                              ? &right
                              : &left);
            }
            INIT_LIST_HEAD(&stack[i]);
            list_splice_init(&left, &stack[i]);
            INIT_LIST_HEAD(&stack[i + 1]);
            list_add_tail(pivot, &stack[i + 1]);
            INIT_LIST_HEAD(&stack[i + 2]);
            list_splice_init(&right, &stack[i + 2]);

            i += 2;
        } else {
            if (!list_empty(&stack_head)) {
                struct list_head *node = stack_head.next;
                list_del(node);
                list_add_tail(node, head);
            }
            i--;
        }
    }
}

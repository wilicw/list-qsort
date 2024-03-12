#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "queue.h"

int main(int argc, char *argv[])
{
    const bool descend = false;
    srand(1);
    LIST_HEAD(head);
    for (int i = 0; i < 100000; i++) {
        element_t *element = malloc(sizeof(element_t));
        element->value = rand();
        list_add_tail(&element->list, &head);
    }

    q_quicksort(&head, descend);

    assert(q_is_sorted(&head, descend));

    return 0;
}

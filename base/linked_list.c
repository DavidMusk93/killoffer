//
// Created by Steve on 6/10/2020.
//

#include "linked_list.h"

#include <stdio.h>

#define LIST struct linked_list_t

static LIST *reverse(LIST *head, LIST **tail) {
    if (!head->next) {
        *tail = head;
        return head;
    }
    (reverse(head->next, tail))->next = head;
    return head;
}

LIST *linked_list_reverse(LIST *head) {
    LIST *tail;
    (reverse(head, &tail))->next = 0;
    return tail;
}

void linked_list_print(LIST *head, FN_linked_list_node_to_string fn) {
    static const char *fmts[] = {"", " -> "};
    char buf[64];
    int first = 0;
    while (head) {
        printf("%s%s", fmts[first ? 1 : (first = 1, 0)], fn(head, buf));
        head = head->next;
    }
    puts(fn(0, buf));
}

LIST *linked_list_from_array(LIST *list, void **array, size_t n) {
    LIST *head = list;
    for (size_t i = 0; i < n; ++i) {
        list->key = array[i];
        list->next = i + 1 == n ? 0 : (list + 1);
        list += 1;
    }
    return head;
}

//#define TEST_LINKED_LIST 1
#if TEST_LINKED_LIST

#include "../macro.h"

static const char *dump_int(LIST *node, char *buf) {
    if (!node) {
        return "";
    }
    sprintf(buf, "%d", *(int *) node->key);
    return buf;
}

MAIN() {
    int data[] = {1, 2, 3, 4, 5, 6, 7, 8};
    const size_t n = dimension_of(data);
    void *array[n];
    FORWARD_FOR(i, 0, n) {
        array[i] = &data[i];
    }
    LIST list[n];
    LIST *h1 = linked_list_from_array(list, array, n);
    linked_list_print(h1, &dump_int);
    LIST *h2 = linked_list_reverse(h1);
    linked_list_print(h2, &dump_int);
    return 0;
}

#endif

#undef LIST
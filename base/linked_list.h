//
// Created by Steve on 6/10/2020.
//

#ifndef KILLOFFER_LINKED_LIST_H
#define KILLOFFER_LINKED_LIST_H

#include <stddef.h>

struct linked_list_t {
    void *key;
    struct linked_list_t *next;
};

typedef const char *(*FN_linked_list_node_to_string)(struct linked_list_t *node, char buf[64]);

struct linked_list_t *linked_list_reverse(struct linked_list_t *head);

void linked_list_print(struct linked_list_t *head, FN_linked_list_node_to_string fn);

struct linked_list_t *linked_list_from_array(struct linked_list_t *list, void **array, size_t n);

#endif //KILLOFFER_LINKED_LIST_H

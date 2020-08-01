//
// Created by Steve on 7/14/2020.
//

#include "common.h"

static ListNode *reverse(ListNode *self, ListNode **head_ptr) {
    if (!self->next) {
        *head_ptr = self;
    } else {
        reverse(self->next, head_ptr)->next = self;
    }
    return self;
}

ListNode *reverse(ListNode *self) {
    if (!self || !self->next) {
        return self;
    }
    ListNode *head;
    reverse(self, &head)->next = nullptr;
    return head;
}
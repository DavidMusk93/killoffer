//
// Created by Steve on 12/25/2020.
//

#include "solver_ex.h"

class Solution {
 public:
  int i, j;
  ListNode *a{}, *b{}, *c{}, *d{}; /*起承转合*/
  ListNode *reverse(ListNode *p) {
    if (!p/*for safe*/|| !p->next) {
      return p;
    }
    if (i++ < j) {
      b = p->next;
      reverse(p->next)->next = p;
    } else {
      d = p->next;
    }
    return p;
  }
  ListNode *reverseBetween(ListNode *head, int m, int n) {
    if (m == n) {
      return head;
    }
    auto p = head;
    i = m, j = n;
    while (--m/*1 based*/) {
      a = p;
      p = p->next;
    }
    c = reverse(p);
    if (a) {
      a->next = b;
    }
    c->next = d;
    return a ? head : b;
  }
};
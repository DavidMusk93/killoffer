//
// Created by Steve on 12/16/2020.
//

#include "solver_ex.h"

#define MEMBER_LIST_1(x) x(_##x)
#define MEMBER_LIST_2(x, ...) MEMBER_LIST_1(x),MEMBER_LIST_1(__VA_ARGS__)
#define MEMBER_LIST_3(x, ...) MEMBER_LIST_1(x),MEMBER_LIST_2(__VA_ARGS__)
#define MEMBER_LIST_4(x, ...) MEMBER_LIST_1(x),MEMBER_LIST_3(__VA_ARGS__)
#define MEMBER_LIST(...) CONCAT(MEMBER_LIST_,ARGS_LEN(__VA_ARGS__))(__VA_ARGS__)

struct Node {
  int val;
  Node *left, *right, *next;
  Node(int _val, Node *_left, Node *_right, Node *_next) : MEMBER_LIST(val, left, right, next) {}
};

class Solution {
 public:
  void connect(Node *leftmost, Node *self) {
    if (self) {
      Node *p{}, *q;
      for (q = leftmost; q; q = q->next) { p = q; }
      if (p && p != self) {
        p->next = self;
      }
      for (q = leftmost; q; q = q->next) {
        if (q->left || q->right) {
          p = q->left ?: q->right;
          break;
        }
      }
      if (self->left) { connect(p, self->left); }
      if (self->right) { connect(p, self->right); }
    }
  }
  Node *connect(Node *root) {
    connect(root, root);
    return root;
  }
};
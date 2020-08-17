//
// Created by Steve on 8/14/2020.
//

#include "solver.h"

class Solution {
public:
    //CONSTRAINS:
    // *at least two nodes
    // *the gaven node is a non-tail node
    void deleteNode(ListNode* node) {
        auto next=node->next;
        //level 1
//        swap(node->val,next->val);
//        node->val=next->val;
//        node->next=next->next;
        //level 2
        *node=*next;
    }
};
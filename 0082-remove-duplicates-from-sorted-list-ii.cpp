//
// Created by Steve on 1/23/2021.
//

#include "solver_ex.h"

class Solution {
public:
    int val{}; // temporary variable
    ListNode *op(ListNode *p) {
        if (p->next) { // Make sure p is not null
            val = p->val;
            if (val == p->next->val) {
                for (p = p->next; p && val == p->val; p = p->next) {}
                if (p) {
                    return op(p);
                }
            }
        }
        return p;
    }

    ListNode *deleteDuplicates(ListNode *p) {
        ListNode *ans{};
        if (!p) {
            return ans;
        }
        ans = p = op(p);
        while (p && p->next) {
            p = p->next = op(p->next);
        }
        return ans;
    }
};
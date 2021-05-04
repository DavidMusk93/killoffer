//
// Created by Steve on 2/6/2021.
//

#include "solver_ex.h"

class Solution {
public:
    int getDecimalValue(ListNode* head) {
        int a=0;
        for(;head;head=head->next){
            a=a<<1;
            a=a+head->val;
        }
        return a;
    }
};
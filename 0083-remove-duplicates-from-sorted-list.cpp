//
// Created by Steve on 11/8/2020.
//

#include "solver_ex.h"

class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if(head){
            ListNode*p=head->next;
            while(p){
                if(p->val!=head->val){
                    break;
                }
                p=p->next;
            }
            head->next=deleteDuplicates(p);
        }
        return head;
    }
};
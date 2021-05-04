//
// Created by Steve on 11/9/2020.
//

#include "solver_ex.h"

class Solution {
public:
    ListNode*op(ListNode*head,int val){
        if(head){
            ListNode*p=head,*q;
            while((q=p->next)&&q->val!=val){
                p=q;
            }
            while(q&&q->val==val){
                q=q->next;
            }
            p->next=removeElements(q,val);
        }
        return head;
    }
    ListNode* removeElements(ListNode* head, int val) {
        while(head&&head->val==val){
            head=head->next;
        }
        return op(head,val);
    }
};
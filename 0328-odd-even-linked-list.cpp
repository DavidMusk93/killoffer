//
// Created by Steve on 9/21/2020.
//

#include "solver_ex.h"

class Solution {
public:
    ListNode* oddEvenList(ListNode* head) {
        if(head){
            ListNode*p,*q;
            p=head,q=head->next;
            if(!q){
                return head;
            }
            ListNode*evenhead=q;
            do{
                if(!p->next||!q->next){
                    break;
                }
                p->next=q->next;
                p=p->next;
                q->next=p->next;
                q=q->next;
            }while(q);
            p->next=evenhead;
        }
        return head;
    }
};

//[1,2,3,4,5]
//[2,1,3,5,6,4,7]
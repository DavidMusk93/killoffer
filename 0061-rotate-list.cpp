//
// Created by Steve on 8/14/2020.
//

#include "solver.h"

class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        if(!head||!head->next){
            return head;
        }
        int n=0;
        auto t=head;
        while(t){
            ++n;
            t=t->next;
        }
        k%=n;
        if(k==0){
            return head;
        }
        auto forward=[](ListNode*head,int n)->ListNode*{
            ListNode*node;
            for(node=head;n--&&node;){
                node=node->next;
            }
            return node;
        };
        ListNode*p1,*p2;
        for(p1=head,p2=forward(head,k);p2->next;){
            p1=p1->next;
            p2=p2->next;
        }
        p2->next=head;
        head=p1->next;
        p1->next=nullptr;
        return head;
    }
};
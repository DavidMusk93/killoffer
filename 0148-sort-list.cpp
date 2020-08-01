//
// Created by Steve on 7/15/2020.
//

#include "common.h"

class Solution {
public:
    ListNode*sortList(ListNode*head){
        if(!head){
            return nullptr;
        }
        return _sortList(head);
    }
    ListNode* _sortList(ListNode* head) {
        if(!head->next){
            return head;
        }
        ListNode*p1,*p2,*t;
        p1=p2=head;
        for(;;){
            p2=p2->next;
            if(!p2||!p2->next){
                break;
            }
            p2=p2->next;
            p1=p1->next;
        }
        p2=p1->next;
        p1->next=nullptr;
        p1=head;
        p1=sortList(p1);
        p2=sortList(p2);
        t=head=p1->val<p2->val?p1:p2;
        (t==p1?p1:p2)=t->next;
        for(;;){
            if(!p1||!p2){
                break;
            }
            t->next=p1->val<p2->val?p1:p2;
            t=t->next;
            (t==p1?p1:p2)=t->next;
        }
        t->next=p1?p1:p2;
        return head;
    }
};
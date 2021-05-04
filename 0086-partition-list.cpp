//
// Created by Steve on 11/17/2020.
//

#include "solver_ex.h"

class Solution {
public:
    void op(ListNode*head,int x){
        auto p=head->next;
        if(p){
            if(p->val>=x){
                op(p,x);
            }
            swap(head->val,p->val);
        }else{
            throw true;
        }
    }
    ListNode* partition(ListNode* head, int x) {
        auto p=head;
        if(p){
            while(p){
                if(p->val>=x){
                    try{
                        op(p,x);
                    }catch(bool&){
                        break;
                    }
                }
                p=p->next;
            }
        }
        return head;
    }
    /**@details Assume A is the less part & B is the greater part, let
     *  @var {a} end of A (head may need to be changed);
     *  @var {b} the beginning of B (update once);
     *  @var {c} previous iterator node;
     *  @var {p} current iterator node.
     */
    ListNode*v2(ListNode*head,int x){
        ListNode*p=head;
        if(p){
            ListNode*a,*b,*c;
            a=b=c=0;
            for(;p;p=p->next){
                if(p->val<x){
                    if(b){
                        if(a){
                            a->next=p;
                        }else{
                            head=p; /*update head*/
                        }
                        c->next=p->next;
                        p->next=b;
                        a=p;
                        p=c;
                    }
                }else if(!b){ /*update b once*/
                    a=c;
                    b=p;
                }
                c=p;
            }
        }
        return head;
    }
};

//[1,4,3,2,5,2,5,7,3,0,13,66]
//3
//[4,5,2]
//3

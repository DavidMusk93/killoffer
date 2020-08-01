//
// Created by Steve on 7/14/2020.
//

#include "common.h"

class Solution {
public:
    bool isPalindrome(ListNode* head) {
        bool res= true;
        ListNode*p1,*p2,*h2;
        for(p1=p2=head;p1&&p2;){
            p1=p1->next;
            if(!p2->next){
                break;
            }
            p2=p2->next->next;
        }
        h2=p2=reverse(p1),p1=head;
        while (p2){
            if(p1->val!=p2->val){
                res= false;
                break;
            }
            p1=p1->next;
            p2=p2->next;
        }
        reverse(h2);
        return res;
    }
};

#include "macro.h"

MAIN(){
    ListNode data[5]={{1}/*explicit may bother*/,{2},{3},{2},{1}};
    int n=dimension_of(data);
    for(int i=1;i<n;++i){
        data[i-1].next=&data[i];
    }
//    auto head=reverse(data);
//    LISTNODE_FOREACH(head,node){
//        LOG("%d",node->val);
//    }
    LOG("%s",Solution().isPalindrome(data)?"true":"false");
    LISTNODE_FOREACH(data,node){
        LOG("%d",node->val);
    }
}
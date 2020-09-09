//
// Created by Steve on 9/5/2020.
//

#include "solver_ex.h"

class Solution {
public:
    ListNode*fn(ListNode*l1,ListNode*l2){
        static ListNode node{};
        auto tail=&node;
        while(l1&&l2){
            auto&l=l1->val<l2->val?l1:l2;
            tail->next=l;
            tail=l;
            l=l->next;
        }
        tail->next=l1?:l2;
        return node.next;
    }
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        const int N=lists.size();
        if(N==0){
            return nullptr;
        }
        auto ans=lists[0];
        for(int i=1;i<N;++i){
            ans=fn(ans,lists[i]);
        }
        return ans;
    }
    ListNode*v2(vector<ListNode*>&lists){
        using Ptr=ListNode*;
        auto fn=[](ListNode*l,ListNode*r){return /*r->val-l->val*/l->val>r->val;/*greater*/}; /*to get TRUE or FALSE*/
        priority_queue<Ptr,std::vector<Ptr>,decltype(fn)> heap(fn);
        for(auto l:lists){
            while(l){
                heap.push(l);
                l=l->next;
            }
        }
        ListNode node{};
        auto tail=&node;
        while(!heap.empty()){
            tail->next=heap.top();
            tail=tail->next;
            heap.pop();
        }
        tail->next=nullptr; /*error prone*/
        return node.next;
    }
};

void f(int&a,int&b){
    auto&c=a<b?a:b;
    c*=c;
}

void g(vector<int>&v){
    for(auto i:v){
        i*=2;
    }
}

MAIN(){
//    int a=3,b=4;
//    f(a,b);
//    LOG("%d,%d",a,b);
//    vector<int> data{1,2,3};
//    g(data);
//    cout<<data;
    vector<ListNode> d1={{1},{4},{5}};
    vector<ListNode> d2={{1},{3},{4}};
    auto l1=ListNode::LinkNode(d1);
    auto l2=ListNode::LinkNode(d2);
    PREREQUISITES(v2);
    vector<ListNode*> lists{l1,l2};
    auto l=INVOKE(lists);
}
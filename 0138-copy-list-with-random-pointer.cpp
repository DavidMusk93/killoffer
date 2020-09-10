//
// Created by Steve on 9/9/2020.
//

#include "solver_ex.h"

class Node{
public:
    int val;
    Node*next;
    Node*random;
    Node()noexcept:Node(0){}
    Node(int val):val{val},next{},random{}{}
};

SOLUTION{
public:
//    static Node pool[1024];
    static vector<Node> pool;
    Node*copyRandomList(Node*head){
        if(!head){
            return nullptr;
        }
        if(pool.empty()){
            pool=vector<Node>(1024,Node{-1});
        }
        auto backup=head;
        int i;
        unordered_map<Node*,int> order;
//        Node*newer[1024]{}; /*@PRIME-2 use `pool` as `newer`*/
//        Node*pre{},*cur{};
        for(i=0;head;++i,/*++k,++n,*/head=head->next){
            auto p=new(&pool[i])Node(head->val); /*@PRIME-1 avoid malloc & free*/
            if(i){
                pool[i-1].next=p;
            }
//            if(pre){
//                pre->next=cur;
//            }
            order[head]=i;
//            newer[i]=p;
//            pre=cur;
        }
        for(i=0,head=backup;head;++i,head=head->next){
            if(head->random){
                auto j=order[head->random];
//                newer[i]->random=newer[j];
                pool[i].random=&pool[j];
            }
        }
        return &pool[0];
    }
};
vector<Node> Solution::pool;
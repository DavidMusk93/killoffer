//
// Created by Steve on 7/14/2020.
//

#ifndef KILLOFFER_COMMON_H
#define KILLOFFER_COMMON_H

#include <vector>

struct ListNode {
    int val;
    ListNode *next;

    ListNode() : ListNode(-1) {}

    ListNode(int x) : val(x), next(nullptr) {}

    static ListNode*LinkNode(std::vector<ListNode>&list){
        const int N=list.size();
        if(N==0){
            return nullptr;
        }
        for(int i=0;i+1<N;++i){
            list[i].next=&list[i+1];
        }
        list.back().next=nullptr;
        return &list.front();
    }
};

struct TreeNode{
    int val;
    TreeNode*left,*right;
    TreeNode():TreeNode(0){}
    TreeNode(int x):TreeNode(x,nullptr,nullptr){}
    TreeNode(int x,TreeNode*left,TreeNode*right):val(x),left(left),right(right){}
};

ListNode *reverse(ListNode *self);

#define LISTNODE_FOREACH(head, x) for(auto*x=head;x;x=x->next)

#include <string>

namespace polyfill {
    class string {
    public:
        string(std::string &s) : n(0), s_(s) {}

        bool starts_with(const std::string &s) {
            const char *p, *q;
            for (p = s_.c_str(), q = s.c_str(); *p && *p == *q; ++p, ++q);
            n = int(p - s_.c_str());
            return !*q;
        }

        bool ends_with(const std::string&s){
            if(s.empty()){
                n=0;
                return true;
            }
            int i,j;
            for(i=(int)s_.size()-1,j=(int)s.size()-1;i>-1&&j>-1&&s_[i]==s[j];--i,--j);
            n=(int)s.size()-1-j;
            return n==s.size();
        }

    public:
        int n;

    private:
        std::string &s_;
    };
}

#endif //KILLOFFER_COMMON_H

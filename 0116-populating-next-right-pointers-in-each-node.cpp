//
// Created by Steve on 8/23/2020.
//

#include "solver.h"

struct Node{
#define ASSIGN(x) x(x)
    int val;
    Node*left,*right,*next;
    Node(int val,Node*left,Node*right,Node*next):ASSIGN(val),ASSIGN(left),ASSIGN(right),ASSIGN(next){}
    Node(int val):Node(val,nullptr,nullptr,nullptr){}
    Node():Node(0,nullptr,nullptr,nullptr){}
#undef ASSIGN
};

class Solution {
public:
    void connect(Node*l,Node*r)/*override*/{
        if(l){
            l->next=r;
            connect(l->right,r->left);
        }
    }

    Node* connect(Node* root) {
        if(root){
            connect(root->left,root->right);
            connect(root->left);
            connect(root->right);
        }
        return root;
    }
};
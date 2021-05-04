//
// Created by Steve on 11/25/2020.
//

#include "solver_ex.h"

class Solution {
public:
    int v1(TreeNode* root) {
        if(root){
            return 1+v1(root->left)+v1(root->right);
        }
        return 0;
    }

    int depth(TreeNode*p){
        int n;
        for(n=1;p->left;++n,p=p->left);
        return n;
    }
    int countNodes(TreeNode*root){
        if(!root){
            return 0;
        }
        if(!root->right){
            //return 1+root->left!=/*'!=' is less precedence than '+'*/nullptr;
            return 1+(root->left?1:0);
        }
        int a,b;
        a=depth(root->left);
        b=depth(root->right);
        if(a==b){
            return (1<<a)/*left child is a full tree*/+countNodes(root->right);
        }
        return (1<<b)/*right is FT*/+countNodes(root->left);
    }
};
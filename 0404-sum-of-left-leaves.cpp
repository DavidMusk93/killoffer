//
// Created by Steve on 9/19/2020.
//

#include "solver_ex.h"

class Solution {
public:
    int ans{};
    void op(TreeNode*root,bool isleft=false){
        if(!root){
            return;
        }
        if(!root->left&&!root->right){
            if(isleft){ans+=root->val;}
        }
        op(root->left,true);
        op(root->right);
    }
    int sumOfLeftLeaves(TreeNode* root) {
        op(root);
        return ans;
    }
};
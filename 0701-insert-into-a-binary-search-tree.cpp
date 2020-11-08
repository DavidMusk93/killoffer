//
// Created by Steve on 10/1/2020.
//

#include "solver_ex.h"

class Solution {
public:
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        auto p=new TreeNode(val);
        if(root){
            auto t=root;
            for(;;){
                if(val<t->val){
                    if(!t->left){
                        t->left=p;
                        break;
                    }
                    t=t->left;
                }else{
                    if(!t->right){
                        t->right=p;
                        break;
                    }
                    t=t->right;
                }
            }
            return root;
        }
        return p;
    }
};
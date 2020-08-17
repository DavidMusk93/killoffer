//
// Created by Steve on 8/15/2020.
//

#include "solver.h"

class Solution {
public:
    int kthSmallest(TreeNode* root, int k) {
        function<void(TreeNode*)> inorder;
        int ans=0;
        inorder=[&inorder,&k,&ans](TreeNode*root){
            if(root){
                inorder(root->left);
                if(++ans==k){
                    ans=root->val;
                    throw 1;
                }
                inorder(root->right);
            }
        };
        try{
            inorder(root);
        }catch(int&){
            return ans;
        }
        return -1;
    }
};
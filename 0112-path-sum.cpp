//
// Created by Steve on 11/9/2020.
//

#include "solver_ex.h"

//class Solution {
//public:
//    void op(TreeNode*root,int left){
//        if(left==0&&!root->left&&!root->right){
//            throw true;
//        }
//#define OP(x) if(x){op(x,left-x->val);}
//        OP(root->left);
//        OP(root->right);
//    }
//    bool hasPathSum(TreeNode* root, int sum) {
//        if(root){
//            try{
//                op(root,sum-root->val);
//            }catch(bool&){
//                return true;
//            }
//        }
//        return false;
//    }
//};

class Solution {
public:
    int left;

    void op(TreeNode *root) {
        bool leaf{true};
        left -= root->val;
        if (root->left) {
            leaf = false;
            op(root->left);
        }
        if (root->right) {
            leaf = false;
            op(root->right);
        }
        if (leaf && !left) {
            throw true;
        }
        left += root->val;
    }

    bool hasPathSum(TreeNode *root, int sum) {
        left = sum;
        if (root) {
            try {
                op(root);
            } catch (bool &) {
                return true;
            }
        }
        return false;
    }
};
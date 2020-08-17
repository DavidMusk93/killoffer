//
// Created by Steve on 8/13/2020.
//

#include "solver.h"

class Solution {
public:
    //CONSTRAINS:
    // 1. NODE value is unique;
    // 2. p & q is differ and both exist.
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        auto find=[](TreeNode*root,TreeNode*p,vector<TreeNode*>&path)->bool{
            while(root){
                path.push_back(root);
                if(root->val==p->val){
                    break;
                }
                root=root->val<p->val?root->right:root->left;
//                if(root->val<p->val){
//                    root=root->right;
//                }else{
//                    root=root->left;
//                }
            }
            return root;
        };
        vector<TreeNode*> v1,v2;
        find(root,p,v1);
        find(root,q,v2);
        int i,n=min(v1.size(),v2.size());
        for(i=0;i<n;++i){
            if(v1[i]!=v2[i]){
                break;
            }
        }
        return (n==v1.size()?v1:v2)[i-1];
    }
};
//
// Created by Steve on 11/8/2020.
//

#include "solver_ex.h"

class Solution {
public:
#define S32_MAX 0x7fffffff
    int ans=S32_MAX;
    void op(TreeNode*root,int k){
        if(k<ans/*fast return*/&&root){
            if(!root->left&&!root->right){
                ans=min(ans,k);
            }else{
                op(root->left,k+1);
                op(root->right,k+1);
            }
        }
    }
    int minDepth(TreeNode* root) {
        if(!root){
            return 0;
        }
        op(root,1);
        return ans;
    }

    int v2(TreeNode*root){
        if(!root){
            return 0;
        }
        deque<TreeNode*> p,q;
//        p.reserve(1024),q.reserve(1024);
        int depth=0;
        p={root};
        while(!p.empty()){
            ++depth;
            for(auto&i:p){
                bool flag=false;
#define RECORD(x) if(x){flag=true;q.push_back(x);}
                RECORD(i->left);
                RECORD(i->right);
                if(!flag){
                    return depth;
                }
            }
            p.swap(q);
            q.clear();
        }
        return depth;
    }
};
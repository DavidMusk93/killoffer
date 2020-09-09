//
// Created by Steve on 9/6/2020.
//

#include "solver_ex.h"

class Solution {
public:
#define POP(q) ({TreeNode*__node{};__node=q.front();q.pop();__node;})
#define PUSH(q,x) if(x){q.push(x);}
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        if(!root){
            return {};
        }
        queue<TreeNode*> level;
        vector<vector<int>> ans;
        level.push(root);
        while(!level.empty()){
            int n=level.size();
            vector<int> t;
            while(n--){
                auto node=POP(level);
                t.push_back(node->val);
                PUSH(level,node->left);
                PUSH(level,node->right);
            }
            ans.push_back(std::move(t));
        }
        for(int i=0,j=ans.size()-1;i<j;++i,--j){
            ans[i].swap(ans[j]);
        }
        return ans;
    }
};
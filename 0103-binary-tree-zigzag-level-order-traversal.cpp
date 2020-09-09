//
// Created by Steve on 8/24/2020.
//

#include "solver_ex.h"

class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        if(!root){
            return {};
        }
        auto traverse=[](vector<TreeNode*>&in,vector<int>&out,bool flag){
            vector<TreeNode*> children;
            for(auto&node:in){
                out.push_back(node->val);
                if(node->left){children.push_back(node->left);}
                if(node->right){children.push_back(node->right);}
            }
            if(flag){
                std::reverse(out.begin(),out.end());
            }
            in.swap(children);
        };
        vector<vector<int>> ans;
        bool flag=false;
        vector<TreeNode*> in{root};
        do{
            vector<int> out;
            traverse(in,out,flag);
            ans.push_back(std::move(out));
            flag=!flag;
        }while(!in.empty());
        return ans;
    }
};
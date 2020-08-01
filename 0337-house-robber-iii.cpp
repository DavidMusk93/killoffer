//
// Created by Steve on 7/28/2020.
//

#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "common.h"

using namespace std;

class Solution {
public:
    //not so fast
    int rob(TreeNode*root){
        if(!root){
            return 0;
        }
        vector<TreeNode*> stack;
        unordered_set<TreeNode*> us;
        //non-recursive post-order traversal
        //  first push -> mark
        //  first peek -> unmark -> push children
        //  second peek -> pop & continue
        stack.push_back(root);
        us.insert(root);
        while(!stack.empty()){
            auto p=stack.back();
            if(us.count(p)){
                us.erase(p);
            }else{
                stack.pop_back();
                Update(p);
                continue;
            }
            if(p->right){
                us.insert(p->right);
                stack.push_back(p->right);
            }
            if(p->left){
                us.insert(p->left);
                stack.push_back(p->left);
            }
        }
        return root->val;
    }
    int rob2(TreeNode* root) {
//#define GET_MAX(x)\
//({\
//    if(!um.count(x)){\
//        um[x]=rob[x];\
//    }\
//    um[x];\
//})
        if(!root){
            return 0;
        }
        int count=root->val;
        if(!root->left&&!root->right){
            return count;
        }
        if(root->left){
            count+=GetMax(root->left->left);
            count+=GetMax(root->left->right);
        }
        if(root->right){
            count+=GetMax(root->right->left);
            count+=GetMax(root->right->right);
        }
        return max(count,GetMax(root->left)+GetMax(root->right));
    }

protected:
    inline void Update(TreeNode*root){
#define UPDATE(x,node) \
do{\
    if(node){\
        x+=node->val;\
    }\
}while(0)
        int a,b;
        a=root->val,b=0;
        if(root->left){
            b+=root->left->val;
            UPDATE(a,root->left->left);
            UPDATE(a,root->left->right);
        }
        if(root->right){
            b+=root->right->val;
            UPDATE(a,root->right->left);
            UPDATE(a,root->right->right);
        }
        root->val=max(a,b);
#undef UPDATE
    }
    inline int GetMax(TreeNode*root){
        if(root){
            if(!um.count(root)){
                um[root]=rob(root);
            }
            return um[root];
        }
        return 0;
    }
    unordered_map<TreeNode*,int> um;
#undef GET_MAX
};
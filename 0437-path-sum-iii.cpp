//
// Created by Steve on 7/21/2020.
//

#include <unordered_set>
#include "common.h"

using namespace std;

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    int pathSum(TreeNode*root,int sum){
        unordered_set<TreeNode*> us;
        return pathSum(root,sum,sum,us);
    }
    int pathSum(TreeNode*root,int left,const int& target,unordered_set<TreeNode*>&us){
        int count=0;
        if(root){
            if(root->val==left){
                ++count;
            }
            count+=pathSum(root->left,left-root->val,target,us);
            count+=pathSum(root->right,left-root->val,target,us);
            if(root->left&&!us.count(root->left)){
                count+=pathSum(root->left,target,target,us);
                us.insert(root->left);
            }
            if(root->right&&!us.count(root->right)){
                count+=pathSum(root->right,target,target,us);
                us.insert(root->right);
            }
        }
        return count;
    }
};
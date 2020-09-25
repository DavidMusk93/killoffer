//
// Created by Steve on 9/21/2020.
//

#include "solver_ex.h"

class Solution {
public:
//    static vector<TreeNode> nodes; /*good practice*/
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        int allocindex=0;
        const int N=nums.size();
        if(!N){
            return nullptr;
        }
//        nodes.resize(N);
        function<TreeNode*(int,int)> op;
        op=[this,&op,&nums,&allocindex](int i,int j)->TreeNode*{
            if(i>j){
                return nullptr;
            }
            if(i==j){
//                return new(&nodes[allocindex++])TreeNode(nums[i]);
                return new TreeNode(nums[i]);
            }
            int k=i+(j-i)/2;
//            auto root=new(&nodes[allocindex++])TreeNode(nums[k]);
            auto root=new TreeNode(nums[k]);
            root->left=op(i,k-1);
            root->right=op(k+1,j);
            return root;
        };
        return op(0,N-1);
//        return &nodes[0];
    }
};

//vector<TreeNode> Solution::nodes{};
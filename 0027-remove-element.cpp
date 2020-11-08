//
// Created by Steve on 11/7/2020.
//

#include "solver_ex.h"

class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        const int N=nums.size();
        int i,j;
        for(i=j=0;j<N;){
            if(nums[j]!=val){
                swap(nums[i++],nums[j++]);
            }else{
                ++j;
            }
        }
        return i;
    }
    int v2(vector<int>&nums,int val){
        int k=0;
        for(auto&i:nums){
            if(i!=val){
                if(&nums[k]!=&i){
                    swap(nums[k],i);
                }
                ++k;
            }
        }
        return k;
    }
};
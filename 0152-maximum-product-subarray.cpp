//
// Created by Steve on 8/3/2020.
//

#include "solver.h"

class Solution {
public:
    int maxProduct(vector<int>& nums) {
        if(nums.size()<2){
            return nums.empty()?0:nums.back();
        }
        auto f=[](const vector<int>&nums)->int{
            int ans=0,a=1;
            for(auto&i:nums){
                if(i==0){
                    a=1;
                    continue;
                }
                a*=i;
                if(a>0){
                    ans=max(ans,a);
                }
            }
            return ans;
        };
        return max(f(nums),({reverse(nums.begin(),nums.end());f(nums);}));
    }
};
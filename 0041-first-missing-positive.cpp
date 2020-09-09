//
// Created by Steve on 8/30/2020.
//

#include "solver_ex.h"

class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        const int N=nums.size();
        int i=0;
        for(;i<N;){
            auto k=nums[i];
            if(k<1||k>N||k==nums[k-1]){
                ++i;
            }else{
                swap(nums[i],nums[k-1]); /*go to right place*/
            }
        }
        for(i=0;i<N;++i){
            if(i+1!=nums[i]){
                return i+1;
            }
        }
        return N+1;
    }
};

MAIN(){
    PREREQUISITES(firstMissingPositive);
    vector<int> data;
    TEST(3,data={1,2,0});
    TEST(2,data={3,4,-1,1});
    TEST(1,data={7,8,9,11,12});
    TEST(4,data={2,1,2,3});
    TEST(4,data={2,3,5,1,-1});
}
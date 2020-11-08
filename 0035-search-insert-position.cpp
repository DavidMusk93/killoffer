//
// Created by Steve on 11/7/2020.
//

#include "solver_ex.h"

class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        if(nums.empty()){
            return 0;
        }
        int i,j,k;
        for(i=0,j=nums.size()-1;i<j;){
            k=i+(j-i)/2;
            if(nums[k]>target){
                j=k-1;
            }else if(nums[k]<target){
                i=k+1;
            }else{
                return k;
            }
        }
        return target<=nums[i]?i:i+1;
    }
};

MAIN(){
    PREREQUISITES(searchInsert);
    vector<int> nums;
    nums={1,3,5,6};
//    TEST(2,nums,5);
    TEST(1,nums,2);
    TEST(4,nums,7);
    TEST(0,nums,0);
    nums={1};
    TEST(0,nums,1);
}
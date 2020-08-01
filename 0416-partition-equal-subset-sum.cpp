//
// Created by Steve on 7/22/2020.
//

#include <vector>
#include <algorithm>
#include <numeric>
#include <functional>

using namespace std;

class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int sum=0;
        sum=accumulate(nums.begin(),nums.end(),0);
//        for(const auto&i:nums){
//            sum+=i;
//        }
        if(sum&1){
            return false;
        }
        sum>>=1;
//        if(any_of(nums.begin(),nums.end(),[&sum](auto i){return i>sum;})){
//            return false;
//        }
        for(const auto&i:nums){
            if(i>=sum){
                return i==sum;
            }
        }
//        sort(nums.begin(),nums.end(),less<>()); //ascend
        sort(nums.begin(),nums.end(),greater<>()); //descend (boost recursion)
//        auto roll=[&sum](int&left,int ball)->bool{
//            if(left&&left>=ball){
//                left-=ball;
//                return true;
//            }
//            return false;
//        };
//        vector<int> bucket(2,sum);
//        for(const auto&i:nums){
//            if(!roll(bucket[0],i)&&!roll(bucket[1],i)){
//                return false;
//            }
//        }
//        return !bucket[0]&&!bucket[1];
        return dfs(nums,0,sum);
    }
    bool dfs(const vector<int>&nums,int i,int left){
        if(i==nums.size()||left<0){
            return false;
        }
        if(left==nums[i]){
            return true;
        }
        return dfs(nums,i+1,left-nums[i])||dfs(nums,i+1,left);
    }
};

#include "macro.h"

MAIN(){
    vector<int> data{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,97,95};
    LOG("%d",Solution().canPartition(data));
}
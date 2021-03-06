//
// Created by Steve on 7/21/2020.
//

#include <vector>

using namespace std;

class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int S) {
        int sum=0;
        for(const auto&n:nums){
            sum+=n;
        }
        if(sum<S){
            return 0;
        }
        sum+=S;
        if(sum&1){
            return 0;
        }
        sum>>=1;
        vector<int> dp(sum+1,0);
        dp[0]=1;
        for(const auto&n:nums){
            for(int i=sum;i>=n;--i){
                dp[i]+=dp[i-n];
            }
        }
        return dp[sum];
    }
};
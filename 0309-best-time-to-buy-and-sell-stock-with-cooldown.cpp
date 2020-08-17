//
// Created by Steve on 8/6/2020.
//

#include "solver.h"

class Solution {
public:
    int maxProfit(vector<int>& prices) {
#define SIGN_MASK (1U<<31U)
        int n=prices.size();
        if(n<2){
            return 0;
        }
        vector<int> dp(n+2,0); //dp[i], max profit which trade from i
        for(int i=n-2;i>=0;--i){
            dp[i]=dp[i+1]; //drop oneself for default
            for(int j=i+1;j<n;++j){
                unsigned delta=prices[i]-prices[j];
                if(delta&SIGN_MASK){
                    dp[i]=max(dp[i],dp[j+2]-static_cast<int>(delta));
                }
            }
        }
        return dp.front();
    }
};

MAIN(){
#define TEST(d,e) EXPECT(solver.maxProfit(d),e)
    Solution solver;
    vector<int> d1={1,2,3,0,2};
    int e1=3;
    TEST(d1,e1);
    vector<int> d2={1,2};
    int e2=1;
    TEST(d2,e2);
}
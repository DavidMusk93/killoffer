//
// Created by Steve on 8/15/2020.
//

#include "solver.h"

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n=prices.size();
        if(n<2){
            return 0;
        }
        vector<int> buy(n,0),sell(n,0);
        buy[0]=-prices[0];
        int ans=0;
        for(int i=1;i<n;++i){
            buy[i]=max(buy[i-1],sell[i-1]-prices[i]);
            sell[i]=max(sell[i-1],buy[i-1]+prices[i]);
            ans=max(ans,sell[i]);
        }
        return ans;
    }
};

MAIN(){
    Solution solver;
    vector<int> data;
    EXPECT(solver.maxProfit(data={7,1,5,3,6,4,}),7);
    EXPECT(solver.maxProfit(data={1,2,3,4,5}),4);
}
//
// Created by Steve on 8/6/2020.
//

#include "solver.h"

class Solution {
public:
    int coinChange(vector<int>&coins,int amount){
        std::sort(coins.begin(),coins.end());
        vector<int> dp(amount+1,-1);
        dp.front()=0;
        for(auto&k:coins){
            for(int i=k;i<=amount;++i){
                if(dp[i-k]!=-1){
                    dp[i]=dp[i]==-1?dp[i-k]+1:min(dp[i-k]+1,dp[i]);
                }
            }
        }
        return dp[amount];
    }
    //not so fast
    int coinChange_DFS(vector<int>&coins,int amount){
        function<void(int,int,int)> dfs;
        int ans=-1;
        sort(coins.begin(),coins.end(),greater<>{});
        dfs=[&dfs,&coins,&ans](int i,int left,int count)->void{
            if(ans!=-1&&ans<=count){
                return;
            }
            if(left==0){
                ans=count;
                return;
            }
            if(i==coins.size()||left<0){
                return;
            }
            for(;i<coins.size();++i){
                int k=left/coins[i];
                for(k=ans==-1?k:ans-count-1;k>-1;--k){
                    dfs(i+1,left-k*coins[i],count+k);
                }
            }
        };
        dfs(0,amount,0);
        return ans;
    }
    int coinChange_PARTIAL(vector<int>& coins, int amount) {
        function<bool(int)> dfs;
        int left=amount,count=0;
        std::sort(coins.begin(),coins.end(),greater<>{});
        dfs=[&dfs,&coins,&amount,&left,&count](int i)->bool{
            if(left<=0){
                return left==0;
            }
            if(i==coins.size()){
                return false;
            }
            int k=left/coins[i];
            count+=k;
            left-=k*coins[i];
            while(k--){
                if(dfs(i+1)){
                    return true;
                }
                --count;
                left+=coins[i];
            }
            return dfs(i+1);
        };
        return dfs(0)?count:-1;
    }
};

MAIN(){
#define TEST(coins,a,e) EXPECT(solver.coinChange(coins,a),e)
    Solution solver;
    vector<int> coins{1,2,5};
    TEST(coins,11,3);
    coins={2};
    TEST(coins,3,-1);
    coins={6,5};
    TEST(coins,16,3);
    TEST(coins,13,-1);
    coins={10,5,2};
    TEST(coins,15,2);
    coins={186,419,83,408};
    TEST(coins,6249,20);
    coins={8,3};
    TEST(coins,12,4);
    coins={800,601,600,1};
    TEST(coins,1201,2);
    coins={3,7,405,436,};
    TEST(coins,8839,25);
    coins={88,227,216,96,209,172,259};
    TEST(coins,6928,28);
}
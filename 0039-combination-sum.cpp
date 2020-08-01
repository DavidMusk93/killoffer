//
// Created by Steve on 7/16/2020.
//

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
#define RET_TYPE vector<vector<int>>
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<RET_TYPE> dp(target+1);
        dp[0].emplace_back(vector<int>{});
        for(auto i:candidates){
            for(int j=i;j<=target;++j){
                if(!dp[j-i].empty()){
                    for(auto v:dp[j-i]){
                        v.push_back(i);
                        dp[j].emplace_back(v);
                    }
                }
            }
        }
        return dp[target];
    }
    RET_TYPE combinationSum2(vector<int>&candidates,int target){
        RET_TYPE res;
        vector<int> v;
        sort(candidates.begin(),candidates.end()); //boost recursion
        combinationSum(candidates,target,0,res,v);
        return res;
    }
    void combinationSum(const vector<int>&candidates,int target,int i,RET_TYPE&res,vector<int>&v){
        if(target==0){ //gotcha
            res.push_back(v);
            return;
        }
        for(;i<candidates.size();++i){
            if(candidates[i]>target){
                break;
            }
            v.push_back(candidates[i]);
            combinationSum(candidates,target-candidates[i],i,res,v);
            v.pop_back();
        }
    }
};
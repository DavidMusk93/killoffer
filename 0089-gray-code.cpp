//
// Created by Steve on 8/13/2020.
//

#include "solver.h"

class Solution {
public:
    vector<int> grayCode(int n/*number of encode bits*/) {
        if(n==0){
            return {0};
        }else if(n==1){
            return {0,1};
        }
        auto generate=[](vector<int>&data,int n){
            auto m=n*2-1;
            for(int i=0;i<n;++i){
                data[i]<<=1;
                data[m-i]=data[i]+1;
            }
        };
        vector<int> ans{0,1};
        ans.resize(1<<n);
        for(int i=1;i<n;++i){
            generate(ans,1<<i);
        }
        return ans;
    }
};
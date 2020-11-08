//
// Created by Steve on 9/29/2020.
//

#include "solver_ex.h"

class Solution {
public:
#define LAYERTYPE std::vector<int>
    static vector<vector<int>> layers;

    void formlayer(int n){
        vector<int> self(n,1);
        auto&pre=layers[n-2];
        for(int i=1;i+1<n;++i){
            self[i]=pre[i-1]+pre[i];
        }
        layers[n-1].swap(self);
    }

    vector<vector<int>> generate(int numRows) {
        const int N=layers.size();
        if(numRows>N){
            layers.resize(numRows);
            for(int i=N+1;i<=numRows;++i){
                formlayer(i);
            }
        }
        vector<LAYERTYPE> ans;
        for(int i=0;i<numRows;++i){
            ans.push_back(layers[i]);
        }
        return ans;
    }
};

vector<LAYERTYPE> Solution::layers={{1},{1,1},{1,2,1}};
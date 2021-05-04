//
// Created by Steve on 11/24/2020.
//

#include "solver_ex.h"

class Solution {
public:
    vector<vector<int>> ans;
    void op(vector<int>&a,int i,int n,int k){
        if(a.size()==k){
            ans.push_back(a);
        }else{
            for(int j=i+1;j<=n;++j){
                a.push_back(j);
                op(a,j,n,k);
                a.pop_back();
            }
        }
    }
    vector<vector<int>> combine(int n, int k) {
        vector<int> a;
        op(a,0,n,k);
        return ans;
    }
};

MAIN(){
    PREREQUISITES(combine);
    cout<<INVOKE(4,2)<<endl;
}

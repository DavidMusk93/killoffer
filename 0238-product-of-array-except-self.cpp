//
// Created by Steve on 8/5/2020.
//

#include "solver.h"

class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int a=1,n=nums.size();
        vector<int> res(n,1);
        for(int i=1;i<n;++i){
            res[i]=nums[i-1]*res[i-1];
        }
        for(int j=n;j>0;--j){
            res[j-1]*=a;
            a*=nums[j];
        }
        return res;
    }
};

MAIN(){
    Solution solver;
    vector<int> d1{1,2,3,4};
    vector<int> e1{24,12,8,6};
    EXPECT(solver.productExceptSelf(d1),e1);
}
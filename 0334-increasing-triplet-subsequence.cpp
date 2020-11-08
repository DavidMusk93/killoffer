//
// Created by Steve on 10/27/2020.
//

#include "solver_ex.h"

class Solution {
public:
    bool increasingTriplet(vector<int>& nums) {
        int a,b;
#define S32_MAX 0x7fffffff
        a=b=S32_MAX;
        for(auto i:nums){
            if(i<=a){
                a=i;
            }else if(i<=b){
                b=i;
            }else{
                return true;
            }
        }
        return false;
    }
};
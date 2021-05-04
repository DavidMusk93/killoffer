//
// Created by Steve on 2/7/2021.
//

#include "solver_ex.h"

class Solution {
public:
    int findNumbers(vector<int>& nums) {
        int a=0;
        for(auto i:nums){
            // meet the constrains (construct sieve)
            if(i<10){

            }else if(i<100){
                ++a;
            }else if(i<1000){

            }else if(i<10000){
                ++a;
            }else if(i==100000){
                ++a;
            }
        }
        return a;
    }
};
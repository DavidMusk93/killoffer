//
// Created by Steve on 2/7/2021.
//

#include "solver_ex.h"

class Solution {
public:
    int numberOfSteps (int num/*non-negative*/) {
        int a=0;
        while(num){
            if(num&1){
                --num;
            }else{
                num>>=1;
            }
            ++a;
        }
        return a;
    }
    int v2(int num){
        int a=0;
        while(num>1){
            a+=1+(num&1);
            num>>=1;
        }
        return num?(a+1):0;
    }
    int v3(int num){
        if(num){
            return __builtin_popcount(num)+31-__builtin_clz(num);
        }
        return 0;
    }
};
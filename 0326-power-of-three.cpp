//
// Created by Steve on 9/21/2020.
//

#include "solver_ex.h"

class Solution {
public:
    bool isPowerOfThree(int n) {
        return n>0&&(n&1)&&1162261467%n==0;
    }
};

int testMaxPowerOfThree(long&max){
#define S32_MAX 0x7fffffff
    long n=81;
    int k=4;
    do{
        if(n*3>S32_MAX){
            max=n;
            break;
        }
        n*=3;
        ++k;
    }while(true);
    return k;
}

MAIN(){
    long max;
    int n=testMaxPowerOfThree(max);
    LOG("%d,%ld",n,max);
}
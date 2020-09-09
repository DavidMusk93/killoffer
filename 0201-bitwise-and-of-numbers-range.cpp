//
// Created by Steve on 8/23/2020.
//

#include "solver.h"

class Solution {
public:
    int rangeBitwiseAnd_v1(int m, int n) {
        if(m==0){
            return 0;
        }
        int k=0;
        while(m!=n){
            m>>=1;
            n>>=1;
            ++k;
        }
        return m?m<<k:0;
    }
    int rangeBitwiseAnd_v2(int m,int n){
#define LEADING_ZERO(x) __builtin_clz(x) /*passing zero may cause undefined-behavior*/
        if(m==0||LEADING_ZERO(m)!=LEADING_ZERO(n)){
            return 0;
        }
        if(m==n){
            return m;
        }
        auto k=32-__builtin_clz(m^n);
        return (m>>k)<<k;
    }
    int rangeBitwiseAnd(int m,int n){
        return rangeBitwiseAnd_v2(m,n);
    }
};

MAIN(){
    PREREQUISITES();
    EXPECT(solver.rangeBitwiseAnd(5,7),4);
    EXPECT(solver.rangeBitwiseAnd(0,1),0);
    EXPECT(solver.rangeBitwiseAnd(246,255),240);
}
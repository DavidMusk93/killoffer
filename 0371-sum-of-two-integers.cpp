//
// Created by Steve on 9/10/2020.
//

#include "solver_ex.h"

//details (-9)+(-5):
// ROUND-0  1111,0111
//          1111,1011
//
// ROUND-1  0000,1100
//          1110,0110
//
// ROUND-2  1110,1010
//          0000,1000
//
// ROUND-3  1110,0010
//          0001,0000
//
// ROUND-4  1111,0010
//          0000,0000

class Solution {
public:
    int getSum(int a, int b) {
        unsigned p,q;
        p=a,q=b;
        while(q){
            auto t=p&q;
            p=p^q;
            q=t<<1U;
        }
        return p;
    }
};

MAIN(){
    PREREQUISITES(getSum);
    TEST(3,1,2);
    TEST(1,-2,3);
    TEST(-1,4,-5);
    TEST(-14,-5,-9);
}
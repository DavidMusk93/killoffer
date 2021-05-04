//
// Created by Steve on 2/11/2021.
//

#include "solver_ex.h"

class Solution {
public:
    //0,1,2,3,4,5,6,7
    //7,5,3,1
    //
    //0,1,2,3,4,5,6
    //6,4,2
    int minOperations(int n) {
        int a=n/2;
        return a*(a+(n&1));
    }
};

MAIN(){
    PREREQUISITES(minOperations);
    //0,1,2
    //2
    TEST(2,3);
    //0,1,2,3,4,5
    //5,3,1
    TEST(9,6);
    TEST(54522,467);
    TEST(197136,888);
    TEST(0,1);
}
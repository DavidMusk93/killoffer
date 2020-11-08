//
// Created by Steve on 10/1/2020.
//

#include "solver_ex.h"

class Solution { /*only 2 & 5 does matter and 5 is less than 2*/
public:
    int trailingZeroes(int n) {
        n/=5;
        if(n>=5){
            n+=trailingZeroes(n);
        }
        return n;
    }
};

MAIN(){
    PREREQUISITES(trailingZeroes);
    TEST(0,3);
    TEST(1,5);
    TEST(105379,421534);
    TEST(12808642,51234581);
}
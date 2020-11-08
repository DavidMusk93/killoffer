//
// Created by Steve on 10/15/2020.
//

#include "solver_ex.h"

class Solution {
public:
    int titleToNumber(string s) {
        int ans{};
        for(auto c:s){
            ans*=26;
            ans+=c-'A'+1;
        }
        return ans;
    }
};

MAIN(){
    PREREQUISITES(titleToNumber);
    TEST(1,"A");
    TEST(28,"AB");
    TEST(701,"ZY");
}


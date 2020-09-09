//
// Created by Steve on 9/7/2020.
//

#include "solver_ex.h"

class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        int carry=1/*plus one*/;
        std::reverse(digits.begin(),digits.end());
        for(auto&i:digits){
            i+=carry;
            if(i>=10){
                carry=i/10;
                i%=10;
                continue;
            }
            carry=0;
            break;
        }
        if(carry){
            digits.push_back(carry);
        }
        std::reverse(digits.begin(),digits.end());
        return digits;
    }
};

MAIN(){
    PREREQUISITES(plusOne);
    vector<int> before,after;
    before={1,2,3,};
    after={1,2,4,};
    TEST(after,before);
    before={4,3,2,1,};
    after={4,3,2,2,};
    TEST(after,before);
    before={9,9,9,};
    after={1,0,0,0,};
    TEST(after,before);
}
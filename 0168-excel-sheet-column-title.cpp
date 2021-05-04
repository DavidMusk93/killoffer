//
// Created by Steve on 11/11/2020.
//

#include "solver_ex.h"

class Solution {
public:
    string convertToTitle(int n) {
        string ans;
        if(n<1){
            return {};
        }
        while(n){
            --n;
            auto t=n%26;
            ans+=t+'A';
            n-=t;
            n/=26;
        }
        reverse(ans.begin(),ans.end());
        return ans;
    }
};

MAIN(){
    PREREQUISITES(convertToTitle);
    TEST("AB",28);
    TEST("RFR",12342);
}
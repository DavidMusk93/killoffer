//
// Created by Steve on 2/7/2021.
//

#include "solver_ex.h"

class Solution {
public:
    int largestAltitude(vector<int>& gain) {
        int a,s;
        a=s=0;
        for(auto i:gain){
            if((s+=i)>a){
                a=s;
            }
        }
        return a;
    }
};

MAIN(){
    PREREQUISITES(largestAltitude);
    vector<int> gain;
    gain={-5,1,5,0,-7};
    TEST(1,gain);
    gain={-4,-3,-2,-1,4,3,2};
    TEST(0,gain);
}

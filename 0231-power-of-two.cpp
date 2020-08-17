//
// Created by Steve on 8/13/2020.
//

#include "solver.h"

class Solution {
public:
    bool isPowerOfTwo(int n) {
        if(n<1){
            return false;
        }
        return (n&(n-1))==/*'==' is higher than '&'*/0;
    }
};

MAIN(){
    Solution solver;
    EXPECT(solver.isPowerOfTwo(0),false);
}
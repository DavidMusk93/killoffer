//
// Created by Steve on 11/7/2020.
//

#include "solver_ex.h"

class Solution {
public:
    int lengthOfLastWord(string s) {
        int i,j,k;
        const int N=s.size();
#define SPACE ' '
        for(j=N-1;s[j]==SPACE;--j);
        for(i=-1,k=0;k<j;++k){
            if(s[k]==SPACE){
                i=k;
            }
        }
        return j-i;
    }
};
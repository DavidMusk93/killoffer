//
// Created by Steve on 8/10/2020.
//

#include "solver.h"

class Solution {
public:
    int countBinarySubstrings(string s) {
//        enum class Order:char{
//            POSITIVE='0',
//            NEGATIVE='1',
//        };
        int n=s.size();
        if(n<2){
            return 0;
        }
        int ans=0;
        for(int k=1;k<n;++k){
            char order;
            if(s[k-1]^s[k]){
                order=s[k-1];
                for(int i=k-1,j=k;i>=0&&j<n;--i,++j){
                    if(s[i]^s[j]&&s[i]==order){
                        ++ans;
                    }else{
                        break;
                    }
                }
            }
        }
        return ans;
    }
};

MAIN(){
    Solution solver;
    EXPECT(solver.countBinarySubstrings("00110011"),6);
    EXPECT(solver.countBinarySubstrings("10101"),4);
}
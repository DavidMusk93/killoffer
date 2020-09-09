//
// Created by Steve on 8/30/2020.
//

#include "solver_ex.h"

class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
#define LEN 9
#define VALIDATE(b,x) \
if(b.test(x)){\
    return false;\
}\
b.set(x)
        bitset<LEN> mask[3][LEN];
        for(int i=0;i<LEN;++i){
            for(int j=0;j<LEN;++j){
                auto k=board[i][j];
                if(k=='.'){
                    continue;
                }
                k-='1';
                auto&b1=mask[0][i];
                VALIDATE(b1,k);
                auto&b2=mask[1][j];
                VALIDATE(b2,k);
                auto&b3=mask[2][(i/3)*3+j/3];
                VALIDATE(b3,k);
            }
        }
        return true;
    }
};
//
// Created by Steve on 9/29/2020.
//

#include "solver_ex.h"

class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
#define FORWARD(_0,_1,_2) for(int _0=_1;_0<_2;++_0)
#define TOPMOST(j) matrix[0][j]
#define LESTMOST(i) matrix[i][0]
        if(matrix.empty()||matrix[0].empty()){
            return;
        }
        const int M=matrix.size(),N=matrix[0].size();
        bool flag=false;
        for(auto i:matrix[0]){if(i==0){flag=true;break;}}
        vector<int> ZEROES(N,0);
        FORWARD(i,1,M){
            FORWARD(j,0,N){
                if(matrix[i][j]==0){
                    TOPMOST(j)=0;
                    LESTMOST(i)=0;
                }
            }
        }
        FORWARD(i,1,M){ /*jump header*/
            if(LESTMOST(i)==0){
                matrix[i]=ZEROES;
                continue;
            }
            FORWARD(j,0,N){
                if(TOPMOST(j)==0){
                    matrix[i][j]=0;
                }
            }
        }
        if(flag){matrix[0]=ZEROES;} /*first line is special*/
    }
};

//[[1,2,3,4],[5,0,7,8],[0,10,11,12],[13,14,15,0]]
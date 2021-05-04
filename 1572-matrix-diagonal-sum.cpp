//
// Created by Steve on 2/6/2021.
//

#include "solver_ex.h"

class Solution {
public:
    int diagonalSum(vector<vector<int>>& mat) {
        int a=0;
        int N=mat.size();
        for(int i=0;i<N;++i){
            int j=N-1-i;
            a=a+mat[i][i]+mat[i][j];
        }
        return (N&1)?(a-mat[N/2][N/2]):a;
    }
    int v2(vector<vector<int>>&mat){
        int a=0;
        int N=mat.size();
        int HN=N/2;
        for(int i=0,j;i<HN;++i){
            j=N-1-i;
            a+=mat[i][i]+mat[i][j]+mat[j][j]+mat[j][i];
        }
        return (N&1)?(a+mat[HN][HN]):a;
    }
};
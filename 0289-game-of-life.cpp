//
// Created by Steve on 10/31/2020.
//

#include "solver_ex.h"

class Solution {
public:
    void gameOfLife(vector<vector<int>>& board) {
        static bool state[2][9]={
                {false,false,false,true,false,false,false,false,false},/*dead*/
                {false,false,true,true,false,false,false,false,false},/*alive*/
        };
        if(board.empty()){
            return;
        }
        const int M=board.size(),N=board[0].size();
        auto isborder=[&M,&N](int i,int j){
            return i<0||j<0||i>=M||j>=N;
        };
        auto op=[&board,&isborder](int i,int j){
            int&self=board[i][j];
            int c=0;
#define COUNT(x,y) if(!isborder(x,y)){c+=board[x][y]&1;}
            COUNT(i-1,j-1);
            COUNT(i-1,j);
            COUNT(i-1,j+1);
            COUNT(i,j-1);
            COUNT(i,j+1);
            COUNT(i+1,j-1);
            COUNT(i+1,j);
            COUNT(i+1,j+1);
#undef COUNT
            if(state[self&1][c]){
                self|=2;
            }
        };
        for(int i=0;i<M;++i){
            for(int j=0;j<N;++j){
                op(i,j);
            }
        }
        for(int i=0;i<M;++i){
            for(int j=0;j<N;++j){
                board[i][j]>>=1;
            }
        }
    }
};
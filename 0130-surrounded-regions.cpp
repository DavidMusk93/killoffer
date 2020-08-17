//
// Created by Steve on 8/13/2020.
//

#include "solver.h"

class Solution {
public:
    void solve(vector<vector<char>>& board) {
//#define IS_BORDER(i,j) ((i)==0||(i)==m-1||(j)==0||(j)==n-1)
#define X 'X'
#define O 'O'
#define REGION vector<pair<int,int>>
        if(board.empty()||board.front().size()<2){
            return;
        }
        const int m=board.size(),n=board.front().size();
        auto is_border=[&m,&n](int i,int j)->bool{
            return i==0||i==m-1||j==0||j==n-1;
        };
        vector<vector<char>> mark(m,vector<char>(n,0));
        function<void(int,int,bool&,REGION&)> dfs;
        REGION region;
        dfs=[&dfs,&is_border,&board,&mark](int i,int j,bool&surrounded,REGION&region){
            if(is_border(i,j)){
//                surrounded=(!/*little precedence*/surrounded)?:board[i][j]==X; //error prone
                if(surrounded&&board[i][j]==O){
                    surrounded=false;
                }
                return;
            }
            do{
                if(mark[i][j]==1){
                    break;
                }
                mark[i][j]=1;
                if(board[i][j]==X){
                    break;
                }
                region.emplace_back(make_pair(i,j));
                dfs(i-1,j,surrounded,region);
                dfs(i+1,j,surrounded,region);
                dfs(i,j-1,surrounded,region);
                dfs(i,j+1,surrounded,region);
            }while(0);
        };
        for(int i=1;i+1<m;++i){
            for(int j=1;j+1<n;++j){
                if(mark[i][j]||board[i][j]==X){
                    continue;
                }
                bool b=true;
                dfs(i,j,b,region);
                if(b){
                    for(auto&p:region){
                        board[p.first][p.second]=X;
                    }
                }
                region.clear();
            }
        }
    }
};
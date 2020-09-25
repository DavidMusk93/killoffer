//
// Created by Steve on 9/19/2020.
//

#include "solver_ex.h"

class Solution {
public:
    void solveSudoku(vector<vector<char>>& board) {
#define N 9
#define X mark[0]
#define Y mark[1]
#define Z mark[2]
#define BSET(x,y,z,k) X[x].set(k),Y[y].set(k),Z[z].set(k)
#define BCLEAR(x,y,z,k) X[x].reset(k),Y[y].reset(k),Z[z].reset(k)
#define BTEST(x,y,z,k) (X[x].test(k)||Y[y].test(k)||Z[z].test(k))
#define DOT '.'
#define ONE '1'
        bitset<N> mark[3][N];
        struct tracepoint{
            int x,y,z,k;
        };
        vector<tracepoint> tracepoints;
        tracepoints.reserve(N*N);
        int traceindex{};
        int x,y,z,k;
        for(x=0;x<N;++x){
            for(y=0;y<N;++y){
                k=board[x][y];
                z=x/3*3+y/3;
                if(k==DOT){
                    tracepoints.push_back({x,y,z,-1});
                }else{
                    BSET(x,y,z,k-ONE);
                }
            }
        }
        do{
            auto&tp=tracepoints[traceindex];
            for(k=tp.k+1;k<N;++k){
                if(!BTEST(tp.x,tp.y,tp.z,k)){
                    tp.k=k;
                    BSET(tp.x,tp.y,tp.z,k);
                    ++traceindex; /*solve next*/
                    break;
                }
            }
            if(k==N){ /*back trace*/
                auto&pre=tracepoints[--traceindex];
                BCLEAR(pre.x,pre.y,pre.z,pre.k);
                tp.k=-1;
            }
        }while(traceindex!=tracepoints.size());
        for(auto&tp:tracepoints){
            board[tp.x][tp.y]=tp.k+ONE;
        }
    }
};

MAIN(){
    PREREQUISITES(solveSudoku);
    vector<vector<char>> board;
    board={{'5','3','.','.','7','.','.','.','.'},
           {'6','.','.','1','9','5','.','.','.'},
           {'.','9','8','.','.','.','.','6','.'},
           {'8','.','.','.','6','.','.','.','3'},
           {'4','.','.','8','.','3','.','.','1'},
           {'7','.','.','.','2','.','.','.','6'},
           {'.','6','.','.','.','.','2','8','.'},
           {'.','.','.','4','1','9','.','.','5'},
           {'.','.','.','.','8','.','.','7','9'}};
    INVOKE(board);
    cout<<board<<endl;
}
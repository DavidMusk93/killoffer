//
// Created by Steve on 9/15/2020.
//

#include "solver_ex.h"

class Solution {
public:
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        if(matrix.empty()||matrix.front().empty()){
            return 0;
        }
        const int ROW=matrix.size(),COL=matrix.front().size();
        int ans=1;
        vector<vector<int>> traced(ROW,vector<int>(COL,0));
        auto isborder=[&ROW,&COL](int i,int j){
            return i<0||j<0||i>=ROW||j>=COL;
        };
        function<int(int,int,int,int)> op;
        op=[&op,&matrix,&traced,&isborder](int i,int j,int k,int d){
            if(isborder(i,j)){
                return d;
            }
            auto&p=traced[i][j];
            auto t=matrix[i][j];
            if(d==0||t>k){
                if(p){
                    return d+p;
                }
                ++d;
                auto m=max({op(i-1,j,t,d),op(i+1,j,t,d),op(i,j-1,t,d),op(i,j+1,t,d)});
                p=m-d+1;
                return m;
            }
            return d;
        };
        for(int i=0;i<ROW;++i){
            for(int j=0;j<COL;++j){
                if(!traced[i][j]){
                    ans=max(ans,op(i,j,0,0));
                }
            }
        }
        return ans;
    }

    int v2(vector<vector<int>>&matrix){
        if(matrix.empty()||matrix[0].empty()){
            return 0;
        }
        const int R=matrix.size(),C=matrix[0].size();
        const int N=R*C;
#define INDEX(_r,_c) ((_r)*C+(_c))
#define FORWARD(_i,_s,_e) for(int _i=_s;_i<_e;++_i)
#define CHECK(_i,_j) \
do{\
    q=matrix[_i][_j];\
    if(p!=q){\
        b=INDEX(_i,_j),k=p<q?b:a;\
        dp[a+b-k].push_back(k);\
        top[k]=0;\
    }\
}while(false)
        vector<vector<int>> dp(N);
        vector<int> top(N,1);
        int p,q,a,b,k;
        /*link*/
        FORWARD(i,0,R){
            FORWARD(j,0,C){
                a=INDEX(i,j);
                p=matrix[i][j];
                if(i>0){
                    CHECK(i-1,j);
                }
                if(j>0){
                    CHECK(i,j-1);
                }
            }
        }
        int ans=0;
        queue<int> queue;
        /*header*/
        FORWARD(i,0,N){
            if(top[i]){
                queue.push(i);
            }
        }
        /*bfs*/
        while(!queue.empty()){
            int n=queue.size();
            ++ans;
            while(n--){
                k=queue.front();
                queue.pop();
                for(auto i:dp[k]){
                    if(ans>=top[i]){
                        top[i]=ans+1;
                        queue.push(i);
                    }
                }
            }
        }
        return ans;
    }
};

MAIN(){
    PREREQUISITES(v2);
    vector<vector<int>> data;
    data={{9,9,4},
          {6,6,8},
          {2,1,1}};
    TEST(4,data);
    data={{3,4,5},
          {3,2,6},
          {2,2,1}};
    TEST(4,data);
    data={{7,7,5},
          {2,4,6},
          {8,2,0}};
    TEST(4,data);
    data={{0,1,2,3,4,5,6,7,8,9},
          {19,18,17,16,15,14,13,12,11,10},
          {20,21,22,23,24,25,26,27,28,29},
          {39,38,37,36,35,34,33,32,31,30},
          {40,41,42,43,44,45,46,47,48,49},
          {59,58,57,56,55,54,53,52,51,50},
          {60,61,62,63,64,65,66,67,68,69},
          {79,78,77,76,75,74,73,72,71,70},
          {80,81,82,83,84,85,86,87,88,89},
          {99,98,97,96,95,94,93,92,91,90},
          {100,101,102,103,104,105,106,107,108,109},
          {119,118,117,116,115,114,113,112,111,110},
          {120,121,122,123,124,125,126,127,128,129},
          {139,138,137,136,135,134,133,132,131,130},
          {0,0,0,0,0,0,0,0,0,0}};
    TEST(140,data);
}
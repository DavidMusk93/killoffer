//
// Created by Steve on 8/2/2020.
//

#include "solver.h"

class Solution {
public:
#define LAND '1'
#define WATER '0'
//#define ACCESS(x,pos,di,dj) (x)[(pos).row+(di)][(pos).col+(dj)]
//#define POS(pos,di,dj) {(pos).row+(di),(pos).col+(dj)}
//#define TOP(x,pos) ACCESS(x,pos,-1,0)
//#define BOTTOM(x,pos) ACCESS(x,pos,1,0)
//#define LEFT(x,pos) ACCESS(x,pos,0,-1)
//#define RIGHT(x,pos) ACCESS(x,pos,0,1)
//#define POS_TOP(pos) POS(pos,-1,0)
//#define POS_BOTTOM(pos) POS(pos,1,0)
//#define POS_LEFT(pos) POS(pos,0,-1)
//#define POS_RIGHT(pos) POS(pos,0,1)
    int numIslands(vector<vector<char>>& grid) {
        if(grid.empty()||grid[0].empty()){
            return 0;
        }
        int m=grid.size(),n=grid.back().size();
        vector<char> line(n+2,WATER);
        for(auto&l:grid){
            l.insert(l.begin(),WATER);
            l.push_back(WATER);
        }
        grid.insert(grid.begin(),line);
        grid.emplace_back(line);
        struct Pos{
            int row,col;
        };
        int res=0;
        for(int i=1;i<=m;++i){
            for(int j=1;j<=n;++j){
                if(grid[i][j]==LAND){
                    grid[i][j]=WATER;
                    ++res;
                    queue<Pos> queue;
                    queue.push({i,j});
                    while(!queue.empty()){
                        auto pos=queue.front();
                        queue.pop();
#define INFECT(di,dj) \
do{\
    Pos adj{pos.row+(di),pos.col+(dj)};\
    auto&p=grid[adj.row][adj.col];\
    if(p==LAND){\
        p=WATER;\
        queue.push(adj);\
    }\
}while(0)
                        INFECT(-1,0);
                        INFECT(1,0);
                        INFECT(0,-1);
                        INFECT(0,1);
                    }
                }
            }
        }
        return res;
#undef CHECK_DELTA
    }
    //simplified & memory efficient, but slower than non-recursion
    int numIslands2(vector<vector<char>>&grid){
        if(grid.empty()||grid.back().empty()){
            return 0;
        }
        int m=grid.size(),n=grid.back().size();
        std::function<void(int,int)> dfs;
        dfs=[&grid,&m,&n,&dfs](int i,int j){
            if(i<0||i>=m||j<0||j>=n||grid[i][j]==WATER){
                return;
            }
            grid[i][j]=WATER;
            dfs(i-1,j);
            dfs(i+1,j);
            dfs(i,j-1);
            dfs(i,j+1);
        };
        int res=0;
        for(int i=0;i<m;++i){
            for(int j=0;j<n;++j){
                if(grid[i][j]==LAND){
                    ++res;
                    dfs(i,j);
                }
            }
        }
        return res;
    }
    //union set
//    int numIslands(vector<vector<char>>& grid){
//        if(grid.empty()||grid.back().empty()){
//            return 0;
//        }
//        int merge=0;
//        int m=grid.size();
//        int n=grid.back().size();
//        vector<int> data;
//        data.reserve(m*n); //avoid re-alloc
//        vector<int*> us(m*n,nullptr);
//        unordered_map<int,int> pairs;
//        for(int i=0;i<m;++i){
//            for(int j=0;j<n;++j){
//                if(grid[i][j]==LAND){
//                    int k=i*n+j;
//                    if(!us[k]){
//                        data.push_back(k);
//                    }
//#define CHECK(di,dj) \
//do{\
//    if(i+(di)<m&&j+(dj)<n&&grid[i+(di)][j+(dj)]==LAND){\
//        int p=k+(di)*n+(dj);\
//        if(!us[p]){\
//            us[p]=us[k]?:&data.back();\
//        }else if(us[p]!=us[k]){\
//            ++merge;\
//        }\
//    }\
//}while(0)
//                    CHECK(1,0);
//                    CHECK(0,1);
//                }
//            }
//        }
//        return (int)data.size()-merge;
//    }
};

//[["1","1","1","1","0"],["1","1","0","1","0"],["1","1","0","0","0"],["0","0","0","0","0"]] #1
//[["1","1","0","0","0"],["1","1","0","0","0"],["0","0","1","0","0"],["0","0","0","1","1"]] #3
//[["1","1","1"],["0","1","0"],["1","1","1"]]                                               #1

MAIN(){
//    vector<vector<char>> grid{{'1','1','1'},{'0','1','0'},{'1','1','1'}};
    vector<vector<char>> grid{
        {'0','1','1'},
        {'1','0','1'},
        {'1','1','1'},
        {'0','0','1'},
        {'1','1','1'},};
    LOG("%d",Solution().numIslands(grid));
}

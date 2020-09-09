//
// Created by Steve on 8/19/2020.
//

#include "solver.h"

#undef CONCAT
#undef _CONCAT
#undef ARGS_LEN

class Solution {
public:
    int removeBoxes(vector<int>& boxes) {
#define MAX_LEN 101
#define V1 vector<int>
#define V2 vector<V1>
#define V3 vector<V2>
        V3 dp(MAX_LEN, V2(MAX_LEN, V1(MAX_LEN, 0)));
//        int dp/*decay by capture*/[101][101][101]={}; //dp(i,j,k) max points for [i,j] && boxes[j]==...==boxes[j+k]
        auto filter_single=[](V1&v)->int{
            int count=0;
            unordered_map<int,int> um;
            for(auto&i:v){
                ++um[i];
            }
            V1 t;
            t.swap(v);
            for(auto&i:t){
                if(um[i]>1){
                    v.push_back(i);
                }else{
                    ++count;
                }
            }
            return count;
        };
        auto count=filter_single(boxes);
        if(boxes.empty()){
            return count;
        }
        function<int(int,int,int)> dfs;
#define ARGS_9(_0,_1,_2,_3,_4,_5,_6,_7,_8,...) _8
#define ARGS_LEN(...) ARGS_9(__VA_ARGS__,8,7,6,5,4,3,2,1,0)
#define _CONCAT(x,y) x##y
#define CONCAT(x,y) _CONCAT(x,y)
#define ACCESS_1(x,i) x[i]
#define ACCESS_2(x,i,j) ACCESS_1(x,i)[j]
#define ACCESS_3(x,i,j,k) ACCESS_2(x,i,j)[k]
#define ACCESS(...) CONCAT(ACCESS_,ARGS_LEN(__VA_ARGS__))(dp,__VA_ARGS__)
        dfs=[&dfs,&boxes,&dp](int i,int j,int k)->int{
//            LOG("%d,%d,%d",i,j,k);
//            if(i==j){
//                return (k+1)*(k+1);
//            }
            if(i>j){
                return 0;
            }
            for(;i<j&&boxes[j-1]==boxes[j];--j,++k);
            auto&p=ACCESS(i,j,k);
            if(p){
                return p;
            }
            p=dfs(i,j-1,0)+(k+1)*(k+1); //option 1
            for(int m=i;m<j;++m){ //option 2
                if(boxes[m]==boxes[j]){
                    p=max(p,dfs(i,m,k+1)+dfs(m+1/*j>m+1*/,j-1,0));
                }
            }
            return p;
        };
        return count+dfs(0,boxes.size()-1,0);
    }
};

MAIN(){
    Solution solver;
    vector<int> boxes;
    EXPECT(solver.removeBoxes(boxes={1,3,2,2,2,3,4,3,1}),23);
}
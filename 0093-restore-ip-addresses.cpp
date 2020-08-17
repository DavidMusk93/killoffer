//
// Created by Steve on 8/9/2020.
//

#include "solver.h"

#define DIFF_1(x) (x[1]-x[0])
#define DIFF_2(x) DIFF_1(x),(x[2]-x[1])
#define DIFF_3(x) DIFF_2(x),(x[3]-x[2])
#define DIFF_4(x) DIFF_3(x),(x[4]-x[3]) //compile time calculate

class Solution {
public:
#define SIZE 4
#define WIDTH 3
//#define MASK (~255U)
#define UPPER "255"
    vector<string> restoreIpAddresses(string s) {
//        static const char*zeros[]={"","0","00","000"};
        const int n=s.size();
        if(n<4||n>12){ //length check
            return {};
        }
        vector<string> ans;
        vector<int> offset(5,0);
        function<void(int,int)> dfs;
        dfs=[&dfs,&ans,&offset,&s,&n](int depth,int i){
            if(depth==SIZE){
                if(i==n){
//                    LOG("%d,%d,%d,%d",DIFF_4(offset));
                    string ip;
                    for(int j=0;j<SIZE;++j){
                        if(j){
                            ip+=".";
                        }
                        ip+=s.substr(offset[j],offset[j+1]-offset[j]);
                    }
                    ans.push_back(move(ip));
                }
            }else if(i<n){
                for(int j=1;j<=WIDTH;++j){
                    if(i+j>n){
                        break;
                    }
                    if(j>1&&s[i]=='0'){ //'0*' is invalid
                        break;
                    }
                    if(j==3&&memcmp(&s[i],UPPER,WIDTH)>0){
                        break;
                    }
                    offset[depth+1]=i+j;
                    dfs(depth+1,i+j);
                }
            }
        };
        dfs(0,0);
        return ans;
    }
#undef UPPER
#undef WIDTH
#undef SIZE
};

MAIN(){
#define S1 "25525511135"
#define S2 "010010"
    Solution solver;
    auto res=solver.restoreIpAddresses(S2);
    for(auto&i:res){
        LOG("%s",i.c_str());
    }
}
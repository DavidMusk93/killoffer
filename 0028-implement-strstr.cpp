//
// Created by Steve on 8/20/2020.
//

#include "solver.h"

class Solution {
public:
    int strStr(string s1,string s2){
        return strStr_DFA(std::move(s1),std::move(s2));
    }
    int strStr_V1(string haystack, string needle) {
        using u8=unsigned char;
        int m=haystack.size(),n=needle.size();
        if(n==0){
            return 0;
        }
        if(m<n){
            return -1;
        }
        int state[256]={};
//        for(int i=n-1;i>=0;--i){
//            state[static_cast<u8>(needle[i])]=n-1-i;
//        }
        for(int i=0;i+1<n;++i){ /*heuristic search*/
            state[static_cast<u8>(needle[i])]=n-1-i;
        }
        for(int i=n-1,j=n-1;i<m;){
//            LOG("%d,%d",i,j);
            auto k=i;
            for(;j>=0&&haystack[i]==needle[j];--i,--j);
            if(j==-1){
                return i+1;
            }
            auto off=state[static_cast<u8>(haystack[k])];
            i=k+(off?:n);
            j=n-1;
        }
        return -1;
    }

    int strStr_DFA/*Deterministic Finite state Automata*/(string haystack,string needle){ //not so fast
#define U8(x) static_cast<unsigned char>(x)
        vector<vector<int>> dfa(needle.size(),vector(126,0));
        int N=haystack.size(),M=needle.size();
        if(M==0){
            return 0;
        }
        if(N<M){
            return -1;
        }
        dfa[0][U8(needle[0])]=1; /*init (critical)*/
        for(int x=0,i=1;i<needle.size();++i){
            auto k=U8(needle[i]);
            dfa[i]=dfa[x];
            dfa[i][k]=i+1;
            x=dfa[x][k];
        }
        int i,j;
        for(i=0,j=0;i<N&&j<M;++i){
            j=dfa[j][U8(haystack[i])];
        }
        if(j==M){
            return i-M;
        }
//        for(auto&i:dfa){
//            cout<<i;
//        }
        return -1;
    }
};

MAIN(){
    Solution solver;
//    LOG("%d",1?:2);
    EXPECT(solver.strStr("",""),0);
    EXPECT(solver.strStr("hello","ll"),2);
    EXPECT(solver.strStr("aaaaa","bba"),-1);
    EXPECT(solver.strStr("onepiecemingqiangsun","ang"),14);
//    solver.strStr_DFA("","ababac");
}
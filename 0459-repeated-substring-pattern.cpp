//
// Created by Steve on 8/24/2020.
//

#define ENHANCED 1
#include "solver.h"

class Solution {
public:
    bool repeatedSubstringPattern(string s) {
        const int N=s.size();
        if(N<2){
            return false;
        }
//        int M=(int)s.find(s[N-1])+1;
//        if(M==N||N%M){
//            return false;
//        }
//        int i,j;
//        for(i=M-1,j=N-1;i>=0&&s[i]==s[j];--i,--j);
//        if(i>=0){
//            return false;
//        }
//        for(i=M;i<N&&memcmp(&s[i],&s[0],M)==0;i+=M);
//        return i==N;
        auto fn=[&s,&N](int M){
            int i=M;
            for(;i<N&&memcmp(&s[0],&s[i],M)==0;i+=M);
            return i==N;
        };
        for(int M=1;(M<<1)<=N;++M){
            if(N%M==0/*invoke function as less as possible*/&&fn(M)){
                return true;
            }
        }
        return false;
    }
};

MAIN(){
    PREREQUISITES(repeatedSubstringPattern);
    EXPECT(INVOKE("abab"),true);
    EXPECT(INVOKE("aba"),false);
    EXPECT(INVOKE("abcabcabcabc"),true);
    EXPECT(INVOKE("abaababaab"),true);
}
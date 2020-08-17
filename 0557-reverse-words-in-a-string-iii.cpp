//
// Created by Steve on 8/12/2020.
//

#include "solver.h"

namespace sun{
    void BufferReverse(char*p,char*q){
        for(;p<q;++p,--q){
            auto t=*p;
            *p=*q;
            *q=t;
        }
    }
}

class Solution {
public:
    string reverseWords(string s) {
#define SPACE ' '
        auto p=&s[0];
        int i,j,n=s.size();
        if(n<2){
            return s;
        }
        for(i=j=0;j<n;++j){
            if(p[j]==SPACE){
                sun::BufferReverse(p+i,p+j-1);
                for(++j;j<n&&p[j]==SPACE;++j);
                i=j;
            }
        }
        sun::BufferReverse(p+i,p+j-1);
        return s;
    }
};

MAIN(){
    string s{"Let's take LeetCode contest"};
    LOG("%s",Solution().reverseWords(s).c_str());
}
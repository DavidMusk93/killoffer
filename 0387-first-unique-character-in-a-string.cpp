//
// Created by Steve on 9/9/2020.
//

#include "solver_ex.h"

SOLUTION{
    int firstUniqChar(string s){
#define BORDERCHECK(N) const int N=s.size();if(N<2){return N?0:-1;}
        BORDERCHECK(N);
//        for(auto&c:s){ /*NORMALIZE*/
//            c-='a';
//        }
        vector<int> v('z'+1,-1);
        for(auto c:s){
            ++v[c];
        }
//        for(auto&c:s){
//            if(!v[c]){
//                return &c-&s[0];
//            }
//        }
        for(int i=0;i<N;++i){
            if(v[s[i]]==0){
                return i;
            }
        }
        return -1;
    }
    int v2(string s){
        BORDERCHECK(N);
        bitset<128> b1,b2;
        for(auto c:s){
            if(b1.test(c)){
                b2.set(c);
            }
            b1.set(c);
        }
        for(auto&c:s){
            if(!b2.test(c)){
                return &c-&s[0];
            }
        }
        return -1;
    }
};

MAIN(){
    PREREQUISITES(v2);
    TEST(0,"leetcode");
    TEST(2,"loveleetcode");
}
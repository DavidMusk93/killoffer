//
// Created by Steve on 9/7/2020.
//

#include "solver_ex.h"

class Solution {
public:
#define ALPHA_SIZE 26
#define ALPHA_ZERO '0'
#define ALPHA_ONE '1'
#define ALPHA_TWO '2'
#define ALPHA_Z 'Z'
    bool preprocess(string&s){
        string t;
        s+=ALPHA_ONE;
        const int N=s.size();
        for(int i=0;i+1<N;++i){
            if(s[i]==ALPHA_ZERO){ /*solo zero meaning invalid*/
                return false;
            }
            if(s[i+1]==ALPHA_ZERO){
                if(s[i]==ALPHA_ONE||s[i]==ALPHA_TWO){ /*10 or 20*/
                    ++i;
                    t.push_back(ALPHA_Z);
                    continue;
                }
                return false;
            }
            t.push_back(s[i]-ALPHA_ZERO);
        }
        s=t;
        return !s.empty();
    }
    int numDecodings(string s) {
        if(!preprocess(s)){
            return 0;
        }
//        dump_blob(&s[0],s.size());
        function<int(int)> op;
        const int N=s.size();
        vector<int> cache(N+1,0);
        cache[N-1]=cache[N]=1;
#define GET(x) (cache[x]?:(cache[x]=op(x)))
        op=[&op,&s,N,&cache](int i)->int{
            if(cache[i]){
                return cache[i];
            }
//            if(i+1==N||i==N){
//                return 1;
//            }
            int res{};
//            res=op(i+1);
            res=GET(i+1);
            int k=s[i]*10+s[i+1];
            if(k<=ALPHA_SIZE){
                res+=GET(i+2);
            }
            return res;
        };
        return op(0);
    }
};

MAIN(){
    PREREQUISITES(numDecodings);
    TEST(2,"12");
    TEST(3,"226");
    TEST(0,"0");
    TEST(1,"10");
    TEST(1,"27");
    TEST(0,"01");
    TEST(1,"110");
    TEST(5898240,"1787897759966261825913315262377298132516969578441236833255596967132573482281598412163216914566534565");
}
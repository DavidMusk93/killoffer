//
// Created by Steve on 8/12/2020.
//

#include "solver.h"

namespace sun{
    using u8=unsigned char;

    string& string_mul(string&s,u8 c){
        u8 over=0;
        string res;
        int n=s.size();
        res.resize(n+1);
        copy(s.begin(),s.end(),res.begin()+1);
        for(int i=n;i>=0;--i){
            auto&p=res[i];
            p=p*c+over;
            over=p/10;
            p%=10;
        }
        s=res.substr(res[0]==0);
        return s;
    }
    string& string_add(string&s1,const string&s2){
        u8 over=0;
        string res;
        int m=s1.size(),n=s2.size();
        auto t=max(m,n); //max
        res.resize(t+1);
        copy(s2.begin(),s2.end(),res.begin()+t-n+1);
        auto off=t-m+1;
        for(int i=t;i>=0;--i){
            auto&p=res[i];
            p+=over;
            if(i>=off){
                p+=s1[i-off];
            }
            over=p/10;
            p%=10;
        }
        s1=res.substr(res[0]==0);
        return s1;
    }
}

class Solution {
public:
    string multiply(string num1, string num2) {
#define ZERO '0'
#define S_ZERO "0"
        if(num1==S_ZERO||num2==S_ZERO){
            return S_ZERO;
        }
        auto preprocess=[](string&num){
            for(auto&i:num){
                i-=ZERO;
            }
        };
        auto postprocess=[](string&num){
            for(auto&i:num){
                i+=ZERO;
            }
        };
        preprocess(num1);
        preprocess(num2);
        string ans;
        int n=num2.size();
        for(auto&c:num2){
            --n;
            if(c==0){
                continue;
            }
            auto t=num1;
            sun::string_mul(t,c)+=string(n,0);
            sun::string_add(ans,t);
        }
        postprocess(ans);
        return ans;
    }
};

MAIN(){
    Solution solver;
    LOG("%s",solver.multiply("123456789","987654321").c_str());
}
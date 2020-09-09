//
// Created by Steve on 9/4/2020.
//

#include "solver_ex.h"

class Solution {
public:
    using container=vector<int>;
    using map=unordered_map<char,int>;
    int gap{};
#define GAP (gap?:k)
public:
    int op(const char*p,const char*q,int k,container v){
        if(p+GAP<=q+1){
//            map m{};
            container vl(26,0);
            for(auto i=p;i<=q;++i){
                if(v[*i]<k){
                    auto j=i+1;
                    for(;j<=q&&(v[*j]-vl[*j])<k;++j);
                    return std::max(op(p,i-1,k,std::move(vl)),op(j,q,k));
                }
                ++vl[*i];
            }
            auto t=static_cast<int>(q-p+1);
            gap=max(gap,t);
            return t;
        }
        return 0;
    }

    int op(const char*p,const char*q,int k){
        if(p+GAP<=q+1){
//            map m{};
            container v(26,0);
            for(auto i=p;i<=q;++i){
                ++v[*i];
            }
            return op(p,q,k,std::move(v));
        }
        return 0;
    }

    int longestSubstring(string s, int k) {
        const int N=s.size();
        if(k<2){
            return N;
        }
        if(N<2){
            return 0;
        }
        //CONSTRAIN: all characters are lower case alpha
        for(auto&i:s){
            i-='a';
        }
        return op(&s.front(),&s.back(),k);
    }
};

MAIN(){
    PREREQUISITES(longestSubstring);
    EXPECT(INVOKE("aaabb",3),3);
    EXPECT(INVOKE("ababbc",2),5);
}
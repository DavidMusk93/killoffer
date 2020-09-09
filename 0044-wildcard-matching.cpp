//
// Created by Steve on 9/6/2020.
//

#include "solver_ex.h"

class Solution {
#define MATCH_SINGLE '?'
#define MATCH_ANY '*'
public:
//    vector<bool> cs;
//    Solution():cs(128,true){
//        cs[MATCH_SINGLE]=false;
//        cs[MATCH_ANY]=false;
//    }
    void eliminate(string&s){ /*merge continuous asterisks as one*/
        if(s.empty()){
            return;
        }
        const int N=s.size();
        string left{};
        left.reserve(N);
        for(int i=0;i+1<N;++i){
            auto c=s[i];
            if(!(c==MATCH_ANY&&c==s[i+1])){
                left.push_back(c);
            }
        }
        left.push_back(s.back());
        left.swap(s);
    }
    bool precheck(const string&s,string p){ /*take no account of ASTERISK & QUESTION mark*/
        p+=char(0);
        const char*a=s.c_str(),*t;
        char*b=&p[0],*q;
        char c;
        for(q=b;(c=*b);++b){
            if(c==MATCH_SINGLE||c==MATCH_ANY){
                *b=0;
                if((t=strstr(a,q))){
                    a=t+(b-q)+(c==MATCH_SINGLE);
                    q=b+1;
                    continue;
                }
                return false;
            }
        }
        return strstr(a,q);
    }
    bool isMatch(string s, string p) {
        eliminate(p);
        function<bool(const char*,const char*)> op;
        op=[&op](const char*a,const char*b)->bool{
//            LOG("%p,%p",a,b);
            if(!*a){
                return !*b||(*b==MATCH_ANY&&op(a,b+1));
            }
            if(!*b){
                return false;
            }
            if(*b==MATCH_SINGLE){
                return op(a+1,b+1);
            }else if(*b==MATCH_ANY){
                return op(a,b+1)||op(a+1,b);
            }
            return *a==*b&&op(a+1,b+1);
        };
        auto sidecheck=[&op](string&s,string&p)->bool{
            auto i=p.find_first_of(MATCH_ANY);
            if(i==string::npos){
                return true;
            }
            auto j=p.find_last_of(MATCH_ANY);
            string t1,t2;
            t2=p.substr(0,i)+p.substr(j+1);
            if(s.size()<t2.size()){
                return false;
            }
            auto k=s.size()-(p.size()-j);
            t1=s.substr(0,i)+s.substr(k+1);
            if(op(t1.c_str(),t2.c_str())){
                s=s.substr(i,k-i+1);
                p=p.substr(i,j-i+1);
                return true;
            }
            return false;
        };
        if(!sidecheck(s,p)){
            return false;
        }
//        LOG("@sidecheck %s,%s",s.c_str(),p.c_str());
        if(!precheck(s,p)){
            return false;
        }
        return op(s.c_str(),p.c_str());
    }
};

MAIN(){
    PREREQUISITES(isMatch);
    TEST(false,"aa","a");
    TEST(true,"aa","*");
    TEST(true,"abc","?*");
    TEST(false,"cb","?a");
    TEST(true,"adceb","*a*b");
    TEST(false,"acdcb","a*c?b");
    TEST(true,"ho","ho**");
    TEST(false,"aaabbbaabaaaaababaabaaabbabbbbbbbbaabababbabbbaaaaba","a*******b");
    TEST(false,"mississippi","m??*ss*?i*pi");
    TEST(true,"mingqiang.sun@weimob.com","mi*g*ng.sun?wei*.c*m");
}
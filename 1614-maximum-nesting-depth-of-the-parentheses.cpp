//
// Created by Steve on 2/6/2021.
//

class Solution {
public:
    int maxDepth(string s) {
#define LP '('
#define RP ')'
        struct A{
            int a,d;
            A():a(0),d(0){}
            A&operator++(){
                if(++a>d){
                    d=a;
                }
                return *this;
            }
            A&operator--(){
                --a;
                return *this;
            }
            int ans(){
                return d;
            }
        };
        A a;
        for(auto c:s){
            if(c==LP){
                ++a;
            }else if(c==RP){
                --a;
            }
        }
        return a.ans();
    }
    int v2(string&s){
        int a,d;
        a=d=0;
        for(auto c:s){
            if(c=='('){
                if(++a>d){
                    d=a;
                }
            }else if(c==')'){
                --a;
            }
        }
        return a;
    }
};
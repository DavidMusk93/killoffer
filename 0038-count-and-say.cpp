//
// Created by Steve on 9/6/2020.
//

#include "solver_ex.h"

class Solution {
#define ANS_SIZE 30
public:
    inline string desc(const string&s,int&offset){
        const int N=s.size();
        if(offset>=N){
            return {};
        }
        auto c=s[offset];
        int count=1;
        while(++offset<N){
            if(s[offset]!=c){
                break;
            }
            ++count;
        }
        return to_string(count)+c;
    }
    string desc(const string&s){
        const int N=s.size();
        int offset{};
        string res;
        while(offset<N){
            res+=desc(s,offset);
        }
        return res;
    }
    static vector<string> as;
    string countAndSay(int n) {
        if(as.front().empty()){
            as[0]="1";
            as[1]="11";
            as[2]="21";
            as[3]="1211";
            as[4]="111221";
            for(int i=5;i<ANS_SIZE;++i){
                as[i]=desc(as[i-1]);
            }
        }
        return as[n-1];
    }
};

vector<string> Solution::as(ANS_SIZE);

MAIN(){
    PREREQUISITES(countAndSay);
    LOG("%s",INVOKE(6).c_str());
    cout<<Solution::as;
}
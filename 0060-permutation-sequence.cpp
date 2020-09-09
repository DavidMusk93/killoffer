//
// Created by Steve on 9/5/2020.
//

#include "solver_ex.h"

class Solution {
public:
    int factorial(int n){
        if(n==1){
            return 1;
        }
        return n*factorial(n-1);
    }
    string getPermutation(int n, int k) {
        string ans;
        vector<char> cs(n,'0');
        int f=1;
        for(int i=1;i<=n;++i){
            cs[i-1]+=i;
            f*=i;
        }
        do{
            if(k==1){
                break;
            }
            f/=n;
            auto i=(k-1)/f;
            k-=i*f;
            ans+=cs[i];
            cs.erase(cs.begin()+i);
        }while(--n);
        for(auto c:cs){ans+=c;}
        return ans;
    }
    void bubble(string&s,int i,int j){
        for(;j>i&&s[j-1]>s[j];--j){
            swap(s[j-1],s[j]);
        }
    }
    string v2(int n,int k){
        string ans(n,'1');
        int f=factorial(n);
        for(int i=1;i<n;++i){
            ans[i]+=i;
        }
        int p=0;
        do{
            if(k==1){
                break;
            }
            f/=n;
            auto q=(k-1)/f;
            k-=q*f;
            swap(ans[p],ans[p+q]);
            bubble(ans,p+1,p+q);
            ++p;
        }while(--n);
        return ans;
    }
};

MAIN(){
    PREREQUISITES(v2);
    TEST("213",3,3);
    TEST("2314",4,9);
}
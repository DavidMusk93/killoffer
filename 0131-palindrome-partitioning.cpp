//
// Created by Steve on 9/9/2020.
//

#include "solver_ex.h"

SOLUTION{
public:
//    struct Loc{
//        int i{};
//        int n{};
//        void update(int p,int q){
//            auto m=q-p+1;
//            if(n<m){
//                i=p;
//                n=m;
//            }
//        }
//    };
    vector<vector<string>> partition(string s){
        const int N=s.size();
        if(N==0){
            return {};
        }
        vector<vector<bool>> dp(N,vector<bool>(N,false));
//        Loc loc{};
        for(int i=N-1;i>=0;--i){
            if(i){
                dp[i][i-1]=true;
            }
            dp[i][i]=true;
            for(int j=i+1;j<N;++j){
                if(s[i]==s[j]&&dp[i+1][j-1]){
                    dp[i][j]=true;
//                    loc.update(i,j);
                }
            }
        }
        vector<vector<string>> ans;
        vector<string> path;
        function<void(int)> op;
        op=[&op,&s,&N,&dp,&ans,&path](int i){
            if(i==N){
                ans.push_back(path);
                return;
            }
            for(int j=i;j<N;++j){
                if(dp[i][j]){
                    path.push_back(s.substr(i,j-i+1));
                    op(j+1);
                    path.pop_back();
                }
            }
        };
        op(0);
        return ans;
//        return {{loc.n?s.substr(loc.i,loc.n):(N?s.substr(N-1):"")}};
    }
};

MAIN(){
    PREREQUISITES(partition);
//    LOG("%s",INVOKE("aab")[0][0].c_str());
//    LOG("%s",INVOKE("abcba")[0][0].c_str());
//    LOG("%s",INVOKE("abba")[0][0].c_str());
    cout<<INVOKE("aab")<<endl;
    cout<<INVOKE("abcbacca")<<endl;
}
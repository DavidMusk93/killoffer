//
// Created by Steve on 7/11/2020.
//

#include <vector>
#include <iostream>

using namespace std;

/**
 * load input
 *     1. cat input.txt | ./a.out
 *     2. ./a.out < input.txt
 *     3. ./a.out < <(cat input.txt)
 * load input from gdb
 *     gdb
 *     (gdb) file a.out
 *     (gdb) run < input.txt
 */
int main(){
    //declaration
    int N,V;
    vector<int> v,w,dp;
    //initialization
    cin>>N>>V;
    v.resize(N),w.resize(N),dp.resize(V+1,0);
    for(auto i=0;i<N;++i){
        cin>>v[i]>>w[i];
    }
    //logic
    for(auto/*auto may be danger when you expect negative*/ i=0;i<N-1;++i){
        for(auto j=V;j>=w[i];--j){
            dp[j]=max(dp[j],dp[j-w[i]]+v[i]);
        }
    }
    if(V>=w[N-1]){
        dp[N]=max(dp[N],dp[N-w[N-1]]+v[N-1]);
    }
    //output
    cout<<dp[V]<<endl;
    return 0;
}
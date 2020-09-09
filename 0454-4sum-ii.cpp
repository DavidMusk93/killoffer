//
// Created by Steve on 8/29/2020.
//

#include "solver_ex.h"

class Solution {
public:
#define ScopedOp(name,op1,op2) \
struct name{\
    name(int&x,int y):x(x),y(y){\
        x=x op1 y;\
    }\
    ~name(){x=x op2 y;}\
    int&x,y;\
}
#define PLUS_X(x) Plus plus_##x{sum,x}
#define MUL_X(x) Mul mul_##x{mul,m##x[x]}
#define LONGER(X) do{if(X.size()>D.size()){X.swap(D);}}while(0)
    ScopedOp(Plus,+,-);
    ScopedOp(Mul,*,/);
    int fourSumCount(vector<int>& A, vector<int>& B, vector<int>& C, vector<int>& D) {
//        unordered_map<int,int> ma,mb,mc,md;
//        auto process=[](vector<int>&v,unordered_map<int,int>&m){
//            set<int> set;
//            for(auto i:v){
//                ++m[i];
//                set.insert(i);
//            }
//            v=vector<int>{set.begin(),set.end()};
//        };
//        LONGER(A);
//        LONGER(B);
//        LONGER(C);
//        process(A,ma);
//        process(B,mb);
//        process(C,mc);
//        process(D,md);
        unordered_map<int,int> me,mf;
        for(auto a:A){
            for(auto b:B){
                ++me[a+b];
            }
        }
        for(auto c:C){
            for(auto d:D){
                ++mf[c+d];
            }
        }
        int ans{};
        for(auto&e:me){
            auto it=mf.find(-e.first);
            if(it!=mf.end()){
                ans+=it->second*e.second;
            }
        }
//        for(auto a:A){
////            mul=ma[a];
//            sum=a;
//            for(auto b:B){
//                PLUS_X(b);
//                auto it=me.find(-sum);
//                if(it!=me.end()){
//                    ans+=it->second;
//                }
////                MUL_X(b);
////                for(auto c:C){
////                    PLUS_X(c);
////                    MUL_X(c);
//////                    LOG("%d,%d,%d,%d",a,b,c,-sum);
////                    auto it=lower_bound(D.begin(),D.end(),-sum);
////                    if(it!=D.end()&&*it==-sum){
////                        ans+=mul*md[-sum];
////                    }
////                }
//            }
//        }
        return ans;
    }
};

MAIN(){
    PREREQUISITES(fourSumCount);
    vector<int> A{1,2},B{-2,-1},C{-1,2},D{0,2};
    LOG("%d",INVOKE(A,B,C,D));
}
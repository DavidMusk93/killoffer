//
// Created by Steve on 8/14/2020.
//

#include "solver.h"

class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        if(n<2){
            if(n==1){
                return {{1}};
            }
            return {{}};
        }
        using Matrix=vector<vector<int>>;
        using BinaryOp=function<void(int&,int&)>;
        auto spiral=[](const BinaryOp& op,Matrix&matrix,int p,int q){
            //+ + + + *
            //@       *
            //@       *
            //@       *
            //@ % % % %
            for(int i=p;i<q;++i){
                op(matrix[p][i],matrix[i][q]);
                op(matrix[i][q],matrix[q][q-i+p]);
                op(matrix[q][q-i+p],matrix[q-i+p][p]);
            }
        };
        Matrix ans(n,vector<int>(n));
        int i,j;
        for(i=0,j=n-1;i<j;++i,--j){
            int v=i==0?1:ans[i][i-1]+1;
//            LOG("@start %d",v);
            for(int k=i;k<j;++k){
                ans[i][k]=v++;
            }
            int delta=j-i;
            auto op=[delta](int&i,int&j){
                j=i+delta;
            };
            spiral(op,ans,i,j);
        }
        if(i==j){
            ans[i][i]=ans[i][i-1]+1;
        }
        return ans;
    }
};

#include <iostream>
#include <iterator>
#include <iomanip>

namespace sun{
    template<size_t N>
struct sticky_ostream:public ostream_iterator<int>::ostream_type{
//        sticky_ostream():ostream(nullptr){}
        template<typename T> std::ostream&operator<<(T&&t){
            return std::cout<<std::setw(N)<<std::forward<T>(t);
        }
    };
}

MAIN(){
    Solution solver;
    auto res=solver.generateMatrix(8);
    sun::sticky_ostream<8> stream{}; //proxy
    for(auto&v:res){
//        copy(v.begin(),v.end(),ostream_iterator<int>(stream/*reference*/,""));
        for(auto&i:v){
            sun::sticky_ostream<8>{}<<i;
        }
        cout<<endl;
    }
}
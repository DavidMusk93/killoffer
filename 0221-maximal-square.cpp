//
// Created by Steve on 8/1/2020.
//

#include <vector>
#include <algorithm>

#include "macro.h"

using namespace std;

//slow, but significant
struct BigNum{
    using Block=unsigned long long;
#define BLOCK (sizeof(BigNum::Block)<<3)
    vector<Block> data;
    BigNum(size_t len){
        data.resize(len);
    }
//    BigNum(size_t len){
//        data.resize(len);
//    }
//    BigNum(BigNum&&other){
//        LOG("move ctor");
//        data.swap(other.data);
//    }
//    BigNum(const BigNum&other){
//        LOG("copy ctor");
//        *this=other;
//    }
//    BigNum&operator=(BigNum&&other){
//        LOG("move assignment");
//        data.swap(other.data);
//        return *this;
//    }
//    BigNum&operator=(const BigNum&other){
//        LOG("copy assignment");
//        data=other.data;
////        data.resize(other.data.size());
////        copy(other.data.begin(),other.data.end(),data.begin());
//        return *this;
//    }
    BigNum&operator&(const BigNum&other){
        if(this==&other){
            return *this;
        }
        for(size_t i=0;i<data.size();++i){
            data[i]&=other.data[i];
        }
        return *this;
    }
    BigNum&operator>>(size_t n){
        for(auto&i:data){
            if(&i!=&data[0]){ //attention
                (&i)[-1]|=(i&n)<<(BLOCK-n);
            }
            i>>=n;
        }
        return *this;
    }
    bool non_zero(){
        return any_of(data.begin(),data.end(),[](auto&i){return i;});
    }
};

class Solution {
public:
#define ZERO '0'
//#define BLOCK 64U
    int maximalSquare(vector<vector<char>>& matrix) {
        //boundary check
        size_t m=matrix.size();
        if(!m){
            return 0;
        }
        size_t n=matrix[0].size();
        if(!n){
            return 0;
        }
        size_t N=n/BLOCK+/*p6*/((n&(BLOCK-1))!=/*p10*/0);
        int res=0;
        vector<BigNum> nums(m,{N});
        for(auto i=0;i<m;++i){
            auto&line=matrix[i];
            auto&num=nums[i];
            for(auto j=0;j<n;++j){
                if(line[j]!=ZERO){
                    num.data[j/BLOCK]|=1ULL/*1U is 32-bit*/<<(j%BLOCK);
                }
            }
        }
        for(auto i=0;i<m;++i){
            auto&p=nums[i];
            auto j=i;
            for(;j<m;++j){
                if(!p.non_zero()){
                    break;
                }
                p&nums[j];
                int w=0,h=j-i+1;
                if(h<res){
                    continue;
                }
                auto p1=p,p2=p;
                for(;w<h&&(p1&p2).non_zero();(p2=p1)>>1,++w);
                res=max(res,w);
            }
        }
        return res*res;
    }
};

//[["1","0","1","0","0"],["1","0","1","1","1"],["1","1","1","1","1"],["1","0","0","1","0"]]
//[["1","0","1","0"],["1","0","1","1"],["1","0","1","1"],["1","1","1","1"]]

MAIN(){
    vector<BigNum> data(10,{1});
    return 0;
}
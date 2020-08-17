//
// Created by Steve on 8/5/2020.
//

#include "solver.h"

#include <cstdlib>

namespace sun{
//    template<typename T>
//    T* bsearch(const T* begin,const T* end,T target){
//        return reinterpret_cast<T*>(std::bsearch(&target,begin,end-begin,sizeof(T),less<T>{}));
//    }
    namespace detail{
        int compare(const void*a,const void*b){
            return *reinterpret_cast<const int*>(a)-*reinterpret_cast<const int*>(b);
        }
    }
    const int* bsearch(const int*begin,const int*end,int target){
        if(begin>=end){
            return nullptr;
        }else if(begin+1==end){
            return *begin==target?begin:nullptr;
        }
        return reinterpret_cast<const int*>(std::bsearch(&target,begin,end-begin,sizeof(int),&detail::compare));
    }
}

class Solution {
public:
#define BOUNDARY_CHECK(x,t) \
do{\
    if(x.empty()||x.back().empty()||t<x.front().front()||t>x.back().back()){\
        return false;\
    }\
}while(0)
#define SHAPE(mat,x,y) \
int x=mat.size(),y=mat.back().size()
    bool searchMatrix(vector<vector<int>>&matrix,int target){
        return searchMatrix_V2(matrix,target);
    }
    bool searchMatrix_V2(vector<vector<int>>&matrix,int target){
#define SIGN_MASK (1U<<31U)
        BOUNDARY_CHECK(matrix,target);
        SHAPE(matrix,row,col);
        for(int i=row-1,j=0;i>=0&&j<col;){
            unsigned delta=target-matrix[i][j]; //fast in binary tree (children choosing)
            if(!delta){
                return true;
            }else if(delta&SIGN_MASK){
                --i;
            }else{
                ++j;
            }
        }
        return false;
#undef SIGN_MASK
    }
    bool searchMatrix_V1(vector<vector<int>>& matrix, int target) {
        BOUNDARY_CHECK(matrix,target);
//        vector<int> diagonal;
        int row=matrix.size(),col=matrix.back().size();
        int i,n=min(row,col);
        for(i=0;i<n;++i){
            const auto&k=matrix[i][i];
            if(k==target){
                return true;
            }else if(k>target){
                break;
            }
        }
        --i;
        auto cursor=matrix.begin()+i;
        for(auto it=matrix.begin();it!=cursor+1;++it){
            int*p=&*it->begin();
            if(sun::bsearch(p+i+1,p+col,target)){
                return true;
            }
        }
        for(auto it=cursor+1;it!=matrix.end();++it){
            int*p=&*it->begin();
            if(sun::bsearch(p,p+i+1,target)){
                return true;
            }
        }
        return false;
    }
};

MAIN(){
#define TEST(data,target,e) EXPECT(solver.searchMatrix(data,target),e)
    Solution solver;
    vector<vector<int>> d1={
            {1,4,7,11,15},
            {2,5,8,12,19},
            {3,6,9,16,22},
            {10,13,14,17,24},
            {18,21,23,26,30},};
    vector<vector<int>> d2={
            {1,3,5,7,9},
            {2,4,6,8,10},
            {11,13,15,17,19},
            {12,14,16,18,20},
            {21,22,23,24,25},};
    vector<vector<int>> d3={
            {-1,3},};
    vector<vector<int>> d4={
            {5},
            {6}};
    EXPECT(solver.searchMatrix(d1,5),true);
    EXPECT(solver.searchMatrix(d1,20),false);
    EXPECT(solver.searchMatrix(d2,11),true);
    EXPECT(solver.searchMatrix(d3,3),true);
    TEST(d4,6,true);
}
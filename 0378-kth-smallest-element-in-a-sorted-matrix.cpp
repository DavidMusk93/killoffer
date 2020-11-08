//
// Created by Steve on 10/15/2020.
//

#include "solver_ex.h"

class Solution {
public:
    void merge(vector<int>&a,const vector<int>&b){
        vector<int> c;
        const int M=a.size(),N=b.size();
        c.reserve(M+N);
        for(int i=0,j=0;i<M||j<N;){
            if(i==M){
                c.push_back(b[j++]);
            }else if(j==N){
                c.push_back(a[i++]);
            }else if(a[i]<b[j]){
                c.push_back(a[i++]);
            }else{
                c.push_back(b[j++]);
            }
        }
        a.swap(c);
    }
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        const int N=matrix.size();
        if(k==1){
            return matrix[0][0];
        }
        if(k==N*N){
            return matrix[N-1][N-1];
        }
        auto nums=matrix[0];
        for(int i=1;i<N;++i){
            merge(nums,matrix[i]);
        }
        return nums[k-1];
    }

    int v2(vector<vector<int>>&matrix,int k){
        const int N=matrix.size();
        int l,m,r;
        l=matrix[0][0],r=matrix[N-1][N-1];
        auto op=[&matrix,&N](int i){
            int row,col,a{};
            for(row=0,col=N-1;row<N&&col>=0;){
                if(matrix[row][col]<=i){
                    a+=col+1;
                    ++row;
                }else{
                    --col;
                }
            }
            return a;
        };
        while(l<r){
            m=l+(r-l)/2;
            if(op(m)<k){
                l=m+1; /*core*/
            }else{
                r=m;
            }
//            LOG("%d,%d",l,r);
        }
        return r;
    }
};

MAIN(){
    PREREQUISITES(v2);
    vector<vector<int>> matrix{{1,5,9},{10,11,13},{12,13,15}};
    INVOKE(matrix,6);
}
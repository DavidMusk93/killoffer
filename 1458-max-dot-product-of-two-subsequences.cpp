//
// Created by Steve on 9/15/2020.
//

#include "solver_ex.h"

class Solution {
public:
    int maxDotProduct(vector<int>& nums1, vector<int>& nums2) {
        int M=nums1.size(),N=nums2.size();
        if(M<N){
            nums1.swap(nums2);
            swap(M,N);
        }
        int ans=nums1[0]*nums2[0];
        function<void(int,int,int)> op;
        op=[&op,&nums1,&nums2,&M,&N,&ans](int i,int j,int k){
            if(j==N){
                if(k&&ans<k){ans=k;}
                return;
            }
            op(i,j+1,k);
            for(;i<M;++i){
                int m=nums1[i]*nums2[j];
                if(ans<m){ans=m;}
                if(m>0){
                    op(i+1,j+1,k+m);
                }
            }
        };
        op(0,0,0);
        return ans;
    }

    int v2(vector<int>&nums1,vector<int>&nums2){
#define SELF dp[i][j]
#define TOP dp[i-1][j]
#define LEFT dp[i][j-1]
#define TOPLEFT dp[i-1][j-1]
        const int M=nums1.size(),N=nums2.size();
        int dp[501][501]{};
        int ans=nums1[0]*nums2[1];
        for(int i=1;i<=M;++i){
            for(int j=1;j<=N;++j){
                auto k=nums1[i-1]*nums2[j-1];
                ans=max(ans,TOPLEFT+k); /*error prone*/
                if(k>0){
                    SELF=max({TOP,LEFT,TOPLEFT+k});
                }else{
                    SELF=max({TOP,LEFT});
                }
//                SELF=max({TOP,LEFT,TOPLEFT+nums1[i-1]*nums2[j-1]});
            }
        }
        return ans;
    }
};

MAIN(){
#define MYTEST(e) TEST(e,v1,v2)
    PREREQUISITES(v2);
    vector<int> v1,v2;
    v1={2,1,-2,5};
    v2={3,0,-6};
    TEST(18,v1,v2);
    v1={3,-2};
    v2={2,-6,7};
    TEST(21,v1,v2);
    v1={-1,-1};
    v2={1,1};
    MYTEST(-1);
    v1={-5,-1,-2};
    v2={3,3,5,5};
    MYTEST(-3);
    v1={3,-1,0};
    v2={4,5,3};
    MYTEST(15);
    v1={0,4,-6,8,10,3,7,15,-15,-1,-6,-13,2,-6,-9,9,-7,-6};
    v2={1,12,9,-7,2,9,-2,0,-10,-12,14,-15,-7,-9,4,15,-6,2};
    MYTEST(1056);
}
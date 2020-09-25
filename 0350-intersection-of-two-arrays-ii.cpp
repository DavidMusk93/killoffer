//
// Created by Steve on 9/14/2020.
//

#include "solver_ex.h"

class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        int M=nums1.size(),N=nums2.size();
        if(!M||!N){
            return {};
        }
        vector<int> ans;
        while(M--){
            for(int j=0;j<N;++j){
                auto&k=nums2[j];
                if(k==nums1[M]){
                    ans.push_back(k);
                    swap(k,nums2[--N]);
                    break;
                }
            }
        }
        return ans;
    }

    vector<int> v2(vector<int>&nums1,vector<int>&nums2){ /*less forward*/
        const int M=nums1.size(),N=nums2.size();
        if(!M||!N){
            return {};
        }
#define SORT(x) std::sort(x.begin(),x.end())
        SORT(nums1),SORT(nums2);
        int i,j;
        vector<int> ans;
        for(i=j=0;i<M&&j<N;){
            int a=nums1[i],b=nums2[j];
            if(a==b){
                ans.push_back(a);
                ++i,++j;
            }else if(a<b){
//                ++i;
                for(++i;i<M&&nums1[i]<b;++i); /*@PRIME-1 using cached greater*/
            }else{
//                ++j;
                for(++j;j<N&&nums2[j]<a;++j);
            }
        }
        return ans;
    }
};

MAIN(){
    PREREQUISITES(v2);
    vector<int> v1,v2,e;
    v1={1,2,2,1};
    v2={2,2};
    e={2,2};
    TEST(e,v1,v2);
    v1={4,9,5};
    v2={9,4,9,8,4};
    e={4,9};
    TEST(e,v1,v2);
}
//
// Created by Steve on 8/18/2020.
//

#include "solver.h"

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
#define VECTOR_EX(v) v.empty()?nullptr:&v[0],v.size()
        function<double(int*,int,int*,int,int)> find;
        find=[&find](int*p1, int len1, int*p2, int len2, int k)->double{
            if(len1>len2){
                return find(p2, len2, p1, len1, k);
            }
            if(len1==0){
                return static_cast<double>(p2[k-1]);
            }
            if(k==1){
                return static_cast<double>(min(*p1,*p2));
            }
            int d1=min(len1,k/2),d2=k-d1;
            if(p1[d1-1]==p2[d2-1]){
                return p1[d1-1];
            }else if(p1[d1-1]<p2[d2-1]){ //proof by contradiction
                return find(p1 + d1, len1 - d1, p2, len2, d2);
            }
            return find(p1, len1, p2 + d2, len2 - d2, d1);
        };
        int k=int(nums1.size()+nums2.size());
        auto ans=find(VECTOR_EX(nums1), VECTOR_EX(nums2), (k>>1)+1);
        if((k&1)==0){
            ans+=find(VECTOR_EX(nums1), VECTOR_EX(nums2), k>>1);
            ans/=2;
        }
        return ans;
    }
};

#include "macro.h"

MAIN(){
    Solution solver;
    vector<int> nums1{1,2,3};
    vector<int> nums2{4,5,6,7};
    LOG("%f",solver.findMedianSortedArrays(nums1,nums2));
    LOG("%f",solver.findMedianSortedArrays(nums1={1,},nums2={2,3,4}));
    LOG("%f",solver.findMedianSortedArrays(nums1={1,2,},nums2={3,4,}));
    LOG("%f",solver.findMedianSortedArrays(nums1={},nums2={1,}));
}
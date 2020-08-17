//
// Created by Steve on 8/13/2020.
//

#include "solver.h"

class Solution {
public:
    //memory efficient (bubble sort) or cpu efficient (external array)
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        vector<int> ans;
        ans.resize(m+n);
        auto p=&ans[0];
        for(int i=0,j=0;i<m||j<n;++p){
            if(i<m&&j<n){
                if(nums1[i]<nums2[j]){
                    *p=nums1[i++];
                }else{
                    *p=nums2[j++];
                }
            }else if(i==m){
                *p=nums2[j++];
            }else{
                *p=nums1[i++];
            }
        }
        nums1=ans;
    }
};
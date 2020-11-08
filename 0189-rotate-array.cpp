//
// Created by Steve on 10/15/2020.
//

#include "solver_ex.h"

class Solution {
public:
    static void moveLeft(vector<int>&nums,int k,int&p,int&q){
        for(;;){
            int t=q-k;
            if(p+k>t+1){
                break;
            }
            for(int i=t,j=q;t<j;--i,--j){
                swap(nums[i],nums[j]);
            }
            q-=k;
        }
        if(p+k!=q+1){
            moveRight(nums,q-p+1-k,p,q);
        }
    }

    static void moveRight(vector<int>&nums,int k,int&p,int&q){
        for(;;){
            int t=p+k;
            if(t+k>q+1){
                break;
            }
            for(int i=p,j=t;i<t;++i,++j){
                swap(nums[i],nums[j]);
            }
            p+=k;
        }
        if(p+k!=q+1){
            moveLeft(nums,q-p+1-k,p,q);
        }
    }

    void rotate(vector<int>& nums, int k) {
        const int N=nums.size();
        k=k%N;
        if(N<2||k==0){
            return;
        }
        int p,q;
        p=0,q=N-1;
        if(k<=N/2){
            moveLeft(nums,k,p,q);
        }else{
            moveRight(nums,N-k,p,q);
        }
    }
};

MAIN(){
    PREREQUISITES(rotate);
    vector<int> data={1,2,3,4,5,6,7};
    vector<int> nums;
    nums=data;
//    p=0,q=nums.size()-1;
//    LOG("%d",Solution::moveLeft(nums,2,p,q));
//    cout<<nums<<","<<p<<","<<q<<endl;
//    nums=data;
//    p=0,q=nums.size()-1;
//    LOG("%d",Solution::moveRight(nums,2,p,q));
//    cout<<nums<<","<<p<<","<<q<<endl;
    INVOKE(nums,3);
    cout<<nums<<endl;
    nums=data;
    INVOKE(nums,5);
    cout<<nums<<endl;
    nums={-1,-100,3,99};
    INVOKE(nums,2);
    cout<<nums<<endl;
}
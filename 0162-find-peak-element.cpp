//
// Created by Steve on 9/21/2020.
//

#include "solver_ex.h"

class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        const int N=nums.size();
        if(N==1){
            return 0;
        }
//        if(N==2){
//            return nums[0]<nums[1];
//        }
        function<void(int,int)> op;
        op=[&op,&nums](int i,int j){
//            LOG("%d,%d",i,j);
            if(i+1==j){ /*only two elements left*/
                throw (i+(nums[i]<nums[j]));
            }
            if(i+1<j){
                int k=i+(j-i)/2;
                if(nums[k]>nums[k-1]&&nums[k]>nums[k+1]){ /*gotta*/
                    throw k;
                }else{
                    int k1,k2;
                    for(k1=k;k1>i;--k1){ /*always make sure the side elements is semi-meet the criteria*/
                        if(nums[k1]<nums[k1-1]){
                            break;
                        }
                    }
                    op(i,k1);
                    for(k2=k;k2<j;++k2){
                        if(nums[k2]<nums[k2+1]){
                            break;
                        }
                    }
                    op(k2,j);
                }
            }
        };
        try{
            op(0,N-1);
        }catch(int&i){
            return i;
        }
        return -1;
    }
};

MAIN(){
    PREREQUISITES(findPeakElement);
    vector<int> nums;
    nums={1,2,3,1};
    TEST(2,nums);
    nums={1,2,1,3,5,6,4};
    TEST(1,nums);
}
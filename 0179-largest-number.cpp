//
// Created by Steve on 10/8/2020.
//

#include "solver_ex.h"

class Solution {
public:
    string largestNumber(vector<int>& nums) {
        if(nums.size()==1){
            return to_string(nums[0]);
        }
        static const long ones[]={1,1,11,111,1111,11111,111111,1111111,11111111,111111111};
        auto rank=[](int i){
            int n=1;
            while(i>=10){
                ++n;
                i/=10;
            }
            return n;
        };
        struct node{
            int i;
            int r;
        };
        vector<node> nodes;
        for(auto i:nums){
            nodes.push_back({i,rank(i)});
        }
        sort(nodes.begin(),nodes.end(),[](const auto&a,const auto&b){return a.i*ones[b.r]>b.i*ones[a.r];});
        string ans;
        for(auto&n:nodes){
            ans+=to_string(n.i);
        }
        if(ans[0]=='0'){
            return "0";
        }
        return ans;
    }
};

MAIN(){
    PREREQUISITES(largestNumber);
    vector<int> nums;
    nums={10,2};
    TEST("210",nums);
    nums={3,30,34,5,9};
    TEST("9534330",nums);
    nums={34323,3432};
    TEST("343234323",nums);
    nums={0,0};
    TEST("0",nums);
}
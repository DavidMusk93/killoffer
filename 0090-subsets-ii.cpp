//
// Created by Steve on 11/27/2020.
//

#include "solver_ex.h"

struct solver{
    virtual ~solver()=default;
    virtual void solve()=0;
};

/* @demo
   nums:1,1,2,2,2,2

          X(genesis)
        /   \
       /     \
      1(0)    2(2) //value(index)
     /  \       \
    /    \       \
   1(1)   2(2)    2(3)
   |      |       |
   2(2)   2(3)    2(4)
   |      |       |
   2(3)   2(4)    2(5)
   |      |
   2(4)   2(5)
   |
   2(5)
 */

struct Worker:public solver{
    Worker(vector<vector<int>>&ans,const vector<int>&nums):ans_(ans),nums_(nums),N_(nums.size()){}
    void op(vector<int>&a,int i){
        if(!a.empty()){
            ans_.push_back(a);
        }
        for(int j=i;i<N_;++i){
            if(i>j&&nums_[i]==nums_[i-1]){
                continue;
            }
            a.push_back(nums_[i]);
            op(a,i+1);
            a.pop_back();
        }
    }
    void solve() override{
        vector<int> a;
        ans_.push_back(a);
        op(a,0);
    }
private:
    vector<vector<int>>&ans_;
    const vector<int>&nums_;
    const int N_;
};

class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        vector<vector<int>> ans;
        if(nums.size()<2){
            ans.emplace_back();
            return nums.empty()?ans:(ans.push_back(nums),ans);
        }
        sort(nums.begin(),nums.end());
//        Worker worker(ans,nums);
        char buf[sizeof(Worker)];
        solver*obj=new(buf)Worker(ans,nums);
        obj->solve();
//        delete obj;
        return ans;
    }
};

MAIN(){
    PREREQUISITES(subsetsWithDup);
    vector<int> nums{1,1,2,2,2,2,3,3,4};
    cout<<INVOKE(nums)<<endl;
}

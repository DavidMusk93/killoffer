//
// Created by Steve on 7/12/2020.
//

#include <deque>
#include <vector>
#include <queue> //not flexible
#include <list>

using namespace std;

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        if(k<2){
            return nums;
        }
        list<int> win; //index container
        vector<int> res;
        for(int i=0;i<nums.size();++i){
            if(win.size()&&win.front()==i-k){ //shift
                win.pop_front();
            }
            /*for(auto it=win.begin();it!=win.end();){
                if(nums[*it]<=nums[i]){
                    it=win.erase(it);
                }else{
                    ++it;
                }
            }*/ //slowly
            while(win.size()&&nums[win.back()]<=nums[i]){ //keep front the maximum
                win.pop_back();
            }
            //erase_if(win,[&](auto x){return nums[x]<=nums[i];}); //cpp20 is cool, but is not supported
            win.push_back(i);
            if(i+1>=k){ //when to push
                res.push_back(nums[win.front()]);
            }
        }
        return res;
    }
};
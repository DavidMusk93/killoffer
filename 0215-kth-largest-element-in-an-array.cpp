//
// Created by Steve on 8/5/2020.
//

#include "solver.h"

class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        priority_queue<int,vector<int>,greater<>> heap;
        for(auto&i:nums){
            if(heap.size()<k){
                heap.push(i);
            }else{
                if(i>heap.top()){
                    heap.pop();
                    heap.push(i);
                }
            }
        }
        return heap.top();
    }
};

MAIN(){
    Solution solver;
    vector<int> d1{3,2,1,5,6,4};
    vector<int> d2{3,2,3,1,2,4,5,5,6};
    EXPECT(solver.findKthLargest(d1,2),5);
    EXPECT(solver.findKthLargest(d2,4),4);
}
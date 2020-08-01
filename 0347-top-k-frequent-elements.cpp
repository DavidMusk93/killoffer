//
// Created by Steve on 7/30/2020.
//

#include <vector>
#include <algorithm> //for std::partition
#include <queue>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int,int> um;
        vector<int> res;
        using T=pair<int,int>;
        auto comp=[](const T&i,const T&j){return i.second>j.second;}; //greater
        priority_queue<T,vector<T>,decltype(comp)> min_heap(comp);
        for(auto&i:nums){
            ++um[i];
        }
        for(auto&p:um){
            if(min_heap.size()<k){
                min_heap.push(p);
            }else{
                auto&top=min_heap.top();
                if(p.second>top.second){
                    min_heap.pop();
                    min_heap.push(p);
                }
            }
        }
        while(!min_heap.empty()){
            res.push_back(min_heap.top().first);
            min_heap.pop();
        }
        return res;
    }
};
//
// Created by Steve on 7/19/2020.
//

#include <vector>
#include <algorithm>
#include <type_traits>

using namespace std;

enum class RelationEnum:char{ //strong enum type
    INTERSECT,
    ISOLATION
};

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        if(intervals.size()<2){
            return intervals;
        }
        sort(intervals.begin(),intervals.end());
        remove_reference_t<decltype(intervals)> res;
//        for(int i=0;i<intervals.size()-1;++i){
//            auto&p1=intervals[i];
//            auto&p2=intervals[i+1];
//            if(p2[0]>p1[1]){
//                res.push_back(p1);
//            }else{
//                p2[0]=p1[0];
//                if(p1[1]>p2[1]){
//                    p2[1]=p1[1];
//                }
//            }
//        }
//        res.push_back(intervals.back());
        res.push_back(intervals.front());
        for(auto interval:intervals){
            auto&tail=res.back(); //error prone
            if(res.empty()||tail[1]<interval[0]){
                res.emplace_back(interval);
            }else{
                tail[1]=max(tail[1],interval[1]);
            }
        }
        return res;
    }
};

#include "macro.h"

MAIN(){
    LOG("%d",(int)sizeof(RelationEnum::INTERSECT));
}
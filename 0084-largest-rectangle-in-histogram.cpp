//
// Created by Steve on 7/23/2020.
//

#include <vector>
#include <algorithm>

#include "macro.h"

using namespace std;

class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
//        return largestRectangleArea(heights,0,heights.size());
        if(heights.size()<2){
            return heights.empty()?0:heights.back();
        }
        heights.push_back(0);
        vector<int> ascend_stack;
        int max_area=0;
        ascend_stack.reserve(heights.size());
        for(int i=0;i<heights.size();++i){
            while(!ascend_stack.empty()&&heights[i]<heights[ascend_stack.back()]){
                int top=heights[ascend_stack.back()];
                ascend_stack.pop_back();
                max_area=max(max_area,top*(i-(ascend_stack.empty()?0:ascend_stack.back()+1)));
            }
            ascend_stack.push_back(i);
        }
        return max_area;
    }
    //incorrect, but inspiring
//    int largestRectangleArea(vector<int>&heights,int i){
//        if(heights.size()-i<2){
//            return heights.size()<=i?0:heights.back();
//        }
//        int min=*min_element(heights.begin()+i,heights.end());
//        int j;
//        for(j=i+1;j<heights.size()&&heights[i]<=heights[j];++j);
//        return ::max({min*((int)heights.size()-i),heights[i]*(j-i),largestRectangleArea(heights,j+1)});
//    }
    //recursion
//    int largestRectangleArea(const vector<int>&heights,int i,int j){
//        if(j==i+2){
//            int a=::min(heights[i],heights[i+1]),b=heights[i]+heights[i+1]-a;
//            return ::max(a<<1,b);
//        }
//        if(j==i+1){
//            return heights[i];
//        }
//        if(j<=i){
//            return 0;
//        }
//        auto&min=*min_element(heights.begin()+i,heights.begin()+j);
////        int k=int(&*it-&heights[i]);
////        int k=int(it-heights.begin()-i);
//        int k=int(&min-&heights[0]);
////        LOG("%d,%d",min,k);
//        return ::max({min*(j-i),largestRectangleArea(heights,i,k),largestRectangleArea(heights,k+1,j)});
//    }
};

MAIN(){
    vector<int> data{2,1,5,6,2,3};
    LOG("%d",Solution().largestRectangleArea(data));
}
//
// Created by Steve on 11/24/2020.
//

#include "solver_ex.h"

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if(matrix.empty()||matrix[0].empty()){
            return false;
        }
        vector<int>*p{};
        for(auto&i:matrix){
//            if(i[0]==target){ /*trivial*/
//                return true;
//            }
            if(i[0]>target){
                break;
            }
            p=&i;
        }
        if(p){
            auto it=lower_bound(p->begin(),p->end(),target);
            return it!=p->end()&&*it==target;
        }
        return false;
    }
};

//[[]]
//1

//[[1]]
//2
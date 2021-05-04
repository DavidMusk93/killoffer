//
// Created by Steve on 2/11/2021.
//

#include "solver_ex.h"

class Solution {
public:
    int countGoodRectangles(vector<vector<int>>& rectangles) {
        struct M{
            int a,c;
            M():a(0),c(0){}
            void add(vector<int>&v){
                int m=v[0]<v[1]?v[0]:v[1];
                if(m>a){
                    a=m;
                    c=1;
                }else if(m==a){
                    ++c;
                }
            }
            int ans(){
                return c;
            }
        };
        M m;
        for(auto&v:rectangles){
            m.add(v);
        }
        return m.ans();
    }
    int v2(vector<vector<int>>&rectangles){
        int a,b,c;
        a=c=0;
        for(auto&v:rectangles){
            b=v[0]<v[1]?v[0]:v[1];
            if(b>a){
                a=b;
                c=1;
            }else if(b==a){
                ++c;
            }
        }
        return c;
    }
};
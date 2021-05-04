//
// Created by Steve on 2/7/2021.
//

#include "solver_ex.h"

class Solution {
public:
    int minTimeToVisitAllPoints(vector<vector<int>>& points) {
#undef ABS
#undef MIN
#define ABS(x) ((x)>0?(x):-/*error-prone*/(x)) // beware of overflow
#define MIN(x,y) ((x)<(y)?(x):(y))
        auto op=[](vector<int>&a,vector<int>&b){
            int i,j,k;
            i=a[0]-b[0];
            j=a[1]-b[1];
            i=ABS(i),j=ABS(j);
            k=i-j;
            return MIN(i,j)+ABS(k);
        };
        int N=points.size();
        int a=0;
        for(int i=1;i<N;++i){
            a+=op(points[i-1],points[i]);
        }
        return a;
    }
    int v2(vector<vector<int>>&points){
        static int i,p,q,N;
        int a=0;
        N=points.size();
        for(i=1;i<N;++i){
#define DIFF(_i,_j) points[_i-1][_j]-points[_i][_j] // overcome handwriting errors
            p=abs(DIFF(i,0));
            q=abs(DIFF(i,1));
            a+=min(p,q)+abs(p-q);
        }
        return a;
    }
};

MAIN(){
    PREREQUISITES(v2);
    vector<vector<int>> points;
    points={{1,1},{3,4},{-1,0}};
    TEST(7,points);
    points={{3,2},{-2,2}};
    TEST(5,points);
}
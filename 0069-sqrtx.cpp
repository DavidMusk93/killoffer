//
// Created by Steve on 8/23/2020.
//

#define ENHANCED 1
#include "solver.h"

class Solution {
public:
    int mySqrt(int x)/*Newton's method*/ {
#define LIMIT 0.1f
        if(x<2){
            return x;
        }
        double/*float may cause error(for 2147395599)*/ ans=x*.5f;
//        while(fabs(ans*ans-x)>LIMIT){
//            ans-=(ans*ans-x)/ans*.5f;
////            LOG("%f",ans);
//        }
        double delta;
        do{
            delta=ans*ans-x;
            ans-=delta/ans*.5;
        }while(delta>LIMIT);
        return int(ans);
    }
};

MAIN(){
    PREREQUISITES(mySqrt);
    EXPECT(INVOKE(1),1);
    EXPECT(INVOKE(4),2);
    EXPECT(INVOKE(8),2);
    EXPECT(INVOKE(2147395599),46339);
}
//
// Created by Steve on 9/9/2020.
//

#include "solver_ex.h"

SOLUTION{
public:
#define S32_MIN 0x80000000
    double myPow(double x,int n){
        if(x==1){
            return x;
        }
        if(x==-1){
            return (n&1?1:-1)*x;
        }
        if(n==0){
            return 1;
        }
        if(n<0){
            if(n==S32_MIN){
                return 0;
            }
            return 1./myPow(x,-n);
        }
        function<double(int)> op;
        op=[&op,&x](int n)->double{
            if(n==1){
                return x;
            }
            auto y=op(n>>1);
            return y*y*(n&1?x:1);
        };
        return op(n);
    }
};

MAIN(){
#define MYTEST(x,n) LOG("%f",INVOKE(x,n))
    PREREQUISITES(myPow);
    LOG("%f",INVOKE(2,10));
    LOG("%f",INVOKE(2.1,3));
    LOG("%f",INVOKE(2,-2));
    LOG("%f",INVOKE(-3.1,-5));
    LOG("%f",INVOKE(1,S32_MIN));
    MYTEST(2,S32_MIN);
}
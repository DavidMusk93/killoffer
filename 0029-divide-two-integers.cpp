//
// Created by Steve on 8/24/2020.
//

#include "solver_ex.h"

class Solution {
#define S32_MIN 0x80000000
#define S32_MAX 0x7fffffff
#define U32(x) static_cast<unsigned>(x)
#define S32(x) static_cast<int>(x)
#define u32 unsigned
#define s32 int
#define MASK 0x80000000u
public:
    int divide(int dividend, int divisor) {
        auto fn=[](u32&left,const u32 d)->u32{
//            LOG("%u,%u",left,d);
            if(left<d){
                return 0U;
            }
            u32 k=0;
            u32 u=d;
            for(;;){
                if(u&MASK/*would overflow*/){
                    break;
                }
                u<<=1U;
                if(u>left){
                    u>>=1U;
                    break;
                }
                ++k;
            }
            return left-=u,1U<<k;
        };
        auto convert=[](int i,u32&sym)->u32{
            sym=i>0;
            if(sym){
                return i; //implicit convert
            }else if(i==S32_MIN){
                return S32_MIN;
            }
            return i*-1;
        };
        u32 ans=0;
        u32 s1,s2;
        u32 p=convert(dividend,s1);
        u32 q=convert(divisor,s2);
        u32 k;
        while((k=fn(p,q))){
            ans+=k;
        }
        if(ans==U32(S32_MIN)){
            return s1^s2?S32_MIN:S32_MAX;
        }
        return s1^s2?S32(ans)*-1:S32(ans);
    }
};

MAIN(){
    PREREQUISITES(divide);
    TEST(3,10,3);
    TEST(S32_MAX,S32_MIN,-1);
    TEST(S32_MIN,S32_MIN,1);
    TEST(-2,7,-3);
    TEST(1,S32_MIN,S32_MIN);
//    LOG("%d,%d,%u",S32_MIN,S32_MAX,U32(S32_MIN));
}
//
// Created by Steve on 9/29/2020.
//

#include "tool.h"

long gcd(long a,long b){
#define ABS(_0) ((_0)>0?(_0):-(_0))
    unsigned long x,y,p,q,t;
//    x=ABS(a);
//    y=ABS(b);
    if(a<0||b<0){
        return gcd(ABS(a),ABS(b));
    }
    x=a,y=b;
//    if(!x||!y){ /*this is the caller's responsibility*/
//        return 1;
//    }
    if(x==y){
        return long(x);
    }
    for(p=0;!(x&1u);++p,x>>=1u);
    for(q=0;!(y&1u);++q,y>>=1u);
    for(;;){
        if(x==y){
            break;
        }
        if(x<y){
            t=x;
            x=y;
            y=t;
        }
        if(y==1){
            break;
        }
        x-=y;
        for(;!(x&1u);x>>=1u);
    }
    return long(y<<(p<q?p:q));
#undef ABS
}

#if TEST_GCD
#include "../macro.h"

MAIN(){
    LOG("%d",gcd(-90,125));
}
#endif
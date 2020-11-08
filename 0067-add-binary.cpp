//
// Created by Steve on 11/7/2020.
//

#include "solver_ex.h"

class Solution {
public:
    string addBinary(string a, string b) {
#define ZERO '0' /*0x30*/
#define ONE '1' /*0x31*/
        if(a.size()<b.size()){
            a.swap(b);
        }
        const int M=a.size(),N=b.size();
        char c=0,t;
        for(int i=M-1,j=N-1;i>=0||j>=0;--i){
            if(j<0){
                if(!c){
                    break;
                }
                a[i]^=1;
                c=a[i]==ZERO;
            }else if(c){
                t=(a[i]|b[j])&1;
//                if(t){
//                    a[i]=((a[i]&b[j])&1)+ZERO;
//                }else{
//                    a[i]=ONE;
//                }
                a[i]=(!t||((a[i]&b[j])&1))+ZERO;
                c=t;
                --j;
            }else{
                t=(a[i]&b[j])&1;
//                if(t){
//                    a[i]=ZERO;
//                }else{
//                    a[i]=((a[i]|b[j])&1)+ZERO;
//                }
                a[i]=ONE-(t||!((a[i]|b[j])&1));
                c=t;
                --j;
            }
        }
        return c?ONE+a:a;
    }
};

MAIN(){
    PREREQUISITES(addBinary);
    string a="1010";
    string b="1011";
    TEST("10101",a,b);
    a="11";
    b="1";
    TEST("100",a,b);
}
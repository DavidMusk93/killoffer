//
// Created by Steve on 9/29/2020.
//

#include "solver_ex.h"

using u64=unsigned long;
struct u128{
#define HMASK (1ULL<<63U)
    u64 h,l;
    u128():u128(0,0){}
    u128(u64 h,u64 l):h(h),l(l){}
    u128&mul2(){
        auto t=l;
        l<<=1U;
        h<<=1U;
        h+=(t&HMASK)!=0;
        return *this;
    }
    u128&mul5(){
        auto&self=*this;
        auto t=self;
        self.mul2().mul2();
//        auto m=t.l>self.l?t.l:self.l;
        l+=t.l;
        h+=t.h;
        h+=l<t.l; /*if overflow happened, the result is less than either of operands*/
        return *this;
    }
};

class Solution {
public:
    static bool op(long a,long b,string&s){
        if(a%b==0){
            return false;
        }
        long K=a,c;
        a*=10;
        for(;;){
            c=a/b;
            a=a-b*c;
            s.push_back('0'+c);
            if(a==0||a==K){
                break;
            }
            a*=10;
        }
        return a;
    }

    static long enlarge(long&a,long&b){
#define UPPER 0xffffffffffff
        long c2,c5;
        for(c2=0;(a<UPPER)&&!(b%2);++c2,b/=2,a*=5);
        for(c5=0;(a<UPPER)&&!(b%5);++c5,b/=5,a*=2);
        return c2+c5;
    }

    string fractionToDecimal(int numerator, int denominator) {
        if(!numerator){
            return "0";
        }
        bool isneg=(numerator<0)^(denominator<0);
        long a,b,c,o;
        a=numerator,b=denominator;
        c=gcd(a,b); /*error prone for S32_MIN*/
        a/=c,b/=c;
        if(a<0){a*=-1;}
        if(b<0){b*=-1;}
        if(a%b==0){
            return to_string((a/b)*(isneg?-1:1));
        }
        o=enlarge(a,b);
        c=a/b;
        a=a-b*c;
        string ans;
        auto isrecur=op(a,b,ans);
        auto t=to_string(c);
        if(o>t.size()){
            t.insert(0,string(o-t.size(),'0')); /*pad zeros at beginning*/
        }
        ans.insert(0,t); /*concat two parts*/
        if(isrecur){
            string::iterator p,q;
            p=ans.begin()+t.size();
            q=ans.begin()+ans.size();
            long k=o;
            while(k--){
                if(p[-1]==q[-1]){
                    --p,--q;
                }else{break;}
            }
            auto pos=p-ans.begin();
            auto s=ans.substr(0,pos)+'('+ans.substr(pos,q-p)+')';
            s.swap(ans);
//            ans.insert(q,')');
//            ans.insert(p,'('); /*insert would invalidate the later iterator*/
//            ans.resize(ans.find(')')+1);
        }
        ans.insert(ans.begin()+t.size()-o,'.');
        if(ans[0]=='.'){ans.insert(ans.begin(),'0');}
        if(isneg){ans.insert(ans.begin(),'-');}
        return ans;
    }
};

MAIN(){
//    u128 x(0,1);
//    int n=31;
//    while(n--){
//        x.mul5();
//    }
//    LOG("%lx,%lx",x.h,x.l);
#define MYTEST(a,b) LOG("%s",INVOKE(a,b).c_str())
    PREREQUISITES(fractionToDecimal);
    MYTEST(1,2);
    MYTEST(2,1);
    MYTEST(2,3);
    MYTEST(1,17);
    MYTEST(1,6);
    MYTEST(89,270);
    MYTEST(1,9000);
    MYTEST(100,90);
    MYTEST(535,2635);
    MYTEST(7,12);
    MYTEST(-1,-2147483648);
    MYTEST(-2147483648,-1);
    MYTEST(2147483647,370000);
}
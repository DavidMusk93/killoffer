//
// Created by Steve on 8/24/2020.
//

#define ENHANCED 1
#include "solver.h"

class Solution {
public:
    bool isPalindrome(string s) {
        string data=s; //a safe buffer
        char *buf=&data[0],*end=buf;
        for(auto/*& is heavy*/ c:s){
            if(isalnum(c)/*count alpha & num*/){
                *end++=tolower(c);
            }
        }
        if(end-buf<2){
            return true;
        }
//        int i,j;
//        for(i=0,j=N-1;i<j;){
//            while(!isalpha(s[i])){++i;} /*trivial*/
//            while(!isalpha(s[j])){--j;}
//        }
        char *p1,*p2;
        for(p1=buf,p2=end-1;p1<p2&&*p1==*p2;++p1,--p2);
        return p1>=p2;
    }
};

MAIN(){
    PREREQUISITES(isPalindrome);
    EXPECT(INVOKE("A man, a plan, a canal: Panama"),true);
    EXPECT(INVOKE("race a car"),false);
    TEST(false,"OP");
    TEST(false,"0P");
}
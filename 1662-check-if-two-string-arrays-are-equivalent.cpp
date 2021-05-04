//
// Created by Steve on 2/7/2021.
//

#include "solver_ex.h"

class Solution {
public:
    bool arrayStringsAreEqual(vector<string>& word1, vector<string>& word2) {
        struct SV{
            const vector<string>&word_ref;
            const unsigned char*p;
            int N,i,j;
            size_t a;
            SV(const vector<string>&word):word_ref(word),p{}{
                i=j=0,N=word.size();
                a=0;
            }
            size_t load(){
#define NS sizeof(size_t)
                if(i==N&&!p){
                    return a;
                }
                if(!p){
                    p=reinterpret_cast<const unsigned char*>(word_ref[i++].c_str());
                }
                for(;j<NS;++j,++p){
                    if(*p){
                        a<<=NS;
                        a+=*p;
                    }else{
                        break;
                    }
                }
                if(!*p){ // boost recursion
                    p=nullptr;
                }
                if(j==NS){
                    j=0;
                    return a;
                }
                return load();
            }
            bool more(){
                return i<N||p;
            }
        };
        SV p(word1),q(word2);
        while(p.more()&&q.more()){
            if(p.load()!=q.load()){
                return false;
            }
        }
        return !p.more()&&!q.more();
    }
};

MAIN(){
    PREREQUISITES(arrayStringsAreEqual);
    vector<string> w1,w2;
    w1={"abc", "d", "defg"};
    w2={"abcddefg"};
    TEST(true,w1,w2);
    w1={"ab", "c"};
    w2={"a", "bc"};
    TEST(true,w1,w2);
    w1={"a", "cb"};
    TEST(false,w1,w2);
    w1={"12345678a"};
    w2={"12345678b"};
    TEST(false,w1,w2);
}

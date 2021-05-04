//
// Created by Steve on 11/20/2020.
//

#include "solver_ex.h"

class Solution {
public:
    string reverseOnlyLetters(string S) {
        if(S.empty()){
            return {};
        }
        static bitset<128> letters;
        if(letters.test('a')==0){
            for(int i=0;i<26;++i){
                letters.set('a'+i);
                letters.set('A'+i);
            }
        }
        for(int i=0,j=S.size()-1;i<j;){
            if(letters.test(S[i])==0){
                ++i;
            }else if(letters.test(S[j])==0){
                --j;
            }else{
                swap(S[i++],S[j--]);
            }
        }
        return S;
    }
};

MAIN(){
    PREREQUISITES(reverseOnlyLetters);
    TEST("ab-cd","dc-ba");
    TEST("a-bC-dEf-ghIj","j-Ih-gfE-dCba");
    TEST("Test1ng-Leet=code-Q!","Qedo1ct-eeLg=ntse-T!");
}
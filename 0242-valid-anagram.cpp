//
// Created by Steve on 10/14/2020.
//

#include "solver_ex.h"

class Solution {
public:
    bool isAnagram(string s, string t) {
        vector<int> v1(26,0),v2(26,0);
        for(auto c:s){
            ++v1[c-'a'];
        }
        for(auto c:t){
            ++v2[c-'a'];
        }
        return v1==v2;
    }
    bool v2(string s,string t){
        int a[26]{};
        if(s.size()!=t.size()){return false;}
        for(auto c:s){
            ++a[c-'a'];
        }
        for(auto c:t){
            --a[c-'a'];
        }
        for(auto i:a){
            if(i){return false;}
        }
        return true;
    }
};

MAIN(){
    PREREQUISITES(v2);
    TEST(true,"anagram","nagaram");
    TEST(false,"rat","car");
}
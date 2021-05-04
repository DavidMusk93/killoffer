//
// Created by Steve on 11/13/2020.
//

#include "solver_ex.h"

class Solution {
public:
    bool wordPattern(string pattern, string s) {
        string table[26];
        unordered_set<string> assigned;
        sun::StringSeparator separator(s);
        for(auto c:pattern){
            if(!separator.next()){
                return false;
            }
            auto sv=separator.getStringView();
            auto t=s.substr(sv.i,sv.j-sv.i);
            auto i=c-'a';
            if(table[i].empty()){
                if(assigned.count(t)){
                    return false;
                }
                assigned.insert(t);
                table[i].swap(t);
            }else if(table[i]!=t){
                return false;
            }
        }
        return !separator.next();
    }
};

MAIN(){
    PREREQUISITES(wordPattern);
    TEST(true,"abba","dog cat cat dog");
    TEST(false,"abba","dog cat cat fish");
    TEST(false,"aaaa","dog cat cat dog");
    TEST(false,"abba","dog dog dog dog");
}
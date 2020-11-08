//
// Created by Steve on 11/2/2020.
//

#include "solver_ex.h"
#include "base/trie.h"

class Solution {
public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        vector<bool> c1(128,true),c2(128,true);
        for(auto c:s){
            if(c1[c]){
                c1[c]=false;
            }
        }
        Trie trie;
        for(auto&i:wordDict){
            trie.insert(i);
            for(auto&c:i){
                if(c2[c]){
                    c2[c]=false;
                }
            }
        }
        if(c1<c2){ /*@CHECK*/
            return {};
        }
        const auto root=trie.getroot();
        vector<vector<int>> ans;
        vector<int> slot;
        const int N=s.size();
        function<void(int,TrieIf*node)> op;
        op=[&op,&N,&slot,&ans,&root,&s](int i,TrieIf*node){
            if(i==N){
                if(node->isword()){
                    ans.push_back(slot);
                }
                return;
            }
            auto t=node->getchild(s[i]);
            if(!t){
                return;
            }
            if(t->isword()){
                slot.push_back(i);
                op(i+1,root); /*restart*/
                slot.pop_back();
            }
            op(i+1,t);
        };
        op(0,root);
        auto fn=[](const string&s,const vector<int>&slot)->string{
            int pre=0;
            string res;
            for(auto i:slot){
                res+=s.substr(pre,i-pre+1)+" ";
                pre=i+1;
            }
            res+=s.substr(pre);
            return res;
        };
        vector<string> res;
        res.reserve(ans.size());
        for(auto&i:ans){
            res.push_back(fn(s,i));
        }
        return res;
    }
};

MAIN(){
    PREREQUISITES(wordBreak);
    string s="catsanddog";
    vector<string> wordDict={"cat","cats","and","sand","dog"};
    cout<<INVOKE(s,wordDict)<<endl;
}

//"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
//["a","aa","aaa","aaaa","aaaaa","aaaaaa","aaaaaaa","aaaaaaaa","aaaaaaaaa","aaaaaaaaaa"]
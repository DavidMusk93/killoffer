//
// Created by Steve on 9/24/2020.
//

#include "solver_ex.h"
#include "base/trie.h"

class Solution {
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        if(board.empty()||board[0].empty()){
            return {};
        }
        const int M=board.size(),N=board[0].size();
        auto isborder=[&M,&N](int i,int j){
            return i<0||i>=M||j<0||j>=N;
        };
        Trie trie;
        for(auto&s:words){
            trie.insert(s);
        }
        auto root=trie.getroot();
        vector<string> ans;
        vector<vector<bool>> mark(M,vector<bool>(N,false));
        unordered_set<string> unique;
        struct context{
            TrieIf*root;
            string s;
        } ctx{root,""},*pctx=&ctx; /*@PRIME-1 using context to reduce memory usage*/
        function<void(int,int)> op;
        op=[&op,&isborder,&board,&ans,&mark,&unique,&pctx](int i,int j){
            if(isborder(i,j)||mark[i][j]){
                return;
            }
            char c=board[i][j];
            auto child=pctx->root->getchild(c);
            if(!child){
                return;
            }
            context old=*pctx;
            pctx->root=child;
//            auto t=pctx->s+c;
            pctx->s+=c;
            if(child->isword()&&unique.insert(pctx->s).second){
                ans.push_back(pctx->s);
            }
            mark[i][j]=true;
            op(i-1,j);
            op(i+1,j);
            op(i,j-1);
            op(i,j+1);
            mark[i][j]=false;
            *pctx=old;
        };
        for(int i=0;i<M;++i){
            for(int j=0;j<N;++j){
                op(i,j);
            }
        }
        return ans;
    }
};

//MAIN(){
//    PREREQUISITES(findWords);
//}
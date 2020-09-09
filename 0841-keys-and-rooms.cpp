//
// Created by Steve on 9/5/2020.
//

#include "solver_ex.h"

class Solution {
public:
    bool canVisitAllRooms(vector<vector<int>>& rooms) {
//        unordered_set<int> us;
//        vector<bool> v(rooms.size(),false);
        const int N=rooms.size();
        bitset<1024> entry;
        entry.set(); /*sets all bits to true*/
        std::function<void(int)> op;
        op=[&op,&entry,&rooms](int i)->void{
            if(entry.test(i)){
                entry.reset(i); /*sets bit to false*/
                for(auto k:rooms[i]){
                    if(k!=i&&entry.test(k)){op(k);}
                }
            }
        };
        op(0);
        for(int i=0;i<N;++i){
            if(entry.test(i)){
                return false;
            }
        }
        return true;
    }
    bool v2(vector<vector<int>>&rooms){
        vector<bool> RIGHT(rooms.size(),true);
        vector<bool> ans(rooms.size(),false);
        ans[0]=true;
        std::function<void(int)> op;
        op=[&op,&rooms,&ans](int i){
            vector<int> v;
            v.swap(rooms[i]);
            for(auto k:v){ /*keep backtrace info in stack frame*/
                ans[k]=true;
                if(!rooms[k].empty()){
                    op(k);
                }
            }
        };
        op(0);
        return ans==RIGHT;
    }
    bool v3(vector<vector<int>>&rooms){
        const int N=rooms.size();
        bitset<1024> entry;
        vector<int> keys;
        keys.reserve(4096);
        int i=0;
        for(;;){
            if(!entry.test(i)){
                entry.set(i);
                for(auto j:rooms[i]){
                    if(j!=i&&!entry.test(j)){
                        keys.push_back(j);
                    }
                }
            }
            if(keys.empty()){
                break;
            }
            i=keys.back();
            keys.pop_back();
        }
//        return entry.count()==rooms.size();
        for(i=0;i<N;++i){
            if(!entry.test(i)){
                return false;
            }
        }
        return true;
    }
};
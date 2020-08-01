//
// Created by Steve on 7/28/2020.
//

#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class Solution {
public:
    struct Value{
        string de;
        double val;
    };
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
        unordered_multimap<string,Value> umm;
        unordered_set<string> us;
        vector<double> res(queries.size(),-1);
        for(int i=0;i<values.size();++i){
            auto&eq=equations[i];
            us.insert(eq[0]);
            if(eq[0]==eq[1]){
                continue;
            }
            us.insert(eq[1]);
            umm.insert({eq[0],Value{eq[1],values[i]}});
            umm.insert({eq[1],Value{eq[0],1/values[i]}});
        }
        auto search=[&umm,this](const auto&from,const auto&to,auto&val)->bool{
            unordered_set<string> traced;
            vector<double> path;
            if(Find(umm,traced,from,to,path)){
                double d=1;
                for(auto&j:path){
                    d*=j;
                }
                val=d;
                return true;
            }
            return false;
        };
        for(int i=0;i<queries.size();++i){
            auto&query=queries[i];
            if(!us.count(query[0])||!us.count(query[1])){
                continue;
            }
            if(query[0]==query[1]){
                res[i]=1;
                continue;
            }
            search(query[0],query[1],res[i]);
        }
        return res;
    }

private:
    bool Find(const unordered_multimap<string,Value>&umm,unordered_set<string>&us,const string&from,const string&to,vector<double>&res){
        auto range=umm.equal_range(from);
        us.insert(from);
        for(auto it=range.first;it!=range.second;++it){
            if(us.count(it->second.de)){
                continue;
            }
            res.push_back(it->second.val);
            if(it->second.de==to||Find(umm,us,it->second.de,to,res)){
                return true;
            }
            res.pop_back();
        }
        us.erase(from);
        return false;
    }
};

#include "macro.h"

MAIN(){
    auto equations=vector<vector<string>>{{"a","b"},{"b","c"}};
    auto values=vector<double>{2,3};
    auto queries=vector<vector<string>>{{"a","c"},{"b","a"},{"a","e"},{"a","a"},{"x","x"}};
    auto res=Solution().calcEquation(equations,values,queries);
    for(auto&i:res){
        LOG("%f",i);
    }
}
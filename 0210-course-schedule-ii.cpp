//
// Created by Steve on 10/31/2020.
//

#include "solver_ex.h"

class Solution {
public:
    vector<int> v2(int numCourses,vector<vector<int>>&prerequisites){
#define BASECHECK(n) \
if((n)<1){return {};}\
if((n)==1){return {0};}
        BASECHECK(numCourses);
        vector<int> ans,h;
        vector<int> indegree(numCourses,0); /*@CORE*/
        vector<vector<int>> graph(numCourses);
        for(auto&p:prerequisites){
            ++indegree[p[0]];
            graph[p[1]].push_back(p[0]);
        }
//        for(auto i:indegree){
//            if(!i){
//                h.push_back(i);
//            }
//        }
        for(int i=0;i<numCourses;++i){
            if(!indegree[i]){
                h.push_back(i);
            }
        }
        for(;;){
            if(h.empty()){
                break;
            }
            vector<int> t;
            for(auto i:h){
                ans.push_back(i);
                for(auto j:graph[i]){
                    if(!(--indegree[j])){
                        t.push_back(j);
                    }
                }
            }
            t.swap(h);
        }
        if(ans.size()!=numCourses){
            ans.clear();
        }
        return ans;
    }
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        if(numCourses<1){
            return {};
        }
        if(numCourses==1){
            return {0};
        }
        vector<int> ans,h;
        vector<vector<int>> graph(numCourses);
        vector<int> timestamp(numCourses,0);
        unordered_set<int> from,to;
        for(auto&p:prerequisites){
            from.insert(p[1]);
            to.insert(p[0]);
            graph[p[1]].push_back(p[0]);
        }
        for(auto i:from){
            if(!to.count(i)){
                h.push_back(i);
            }
        }
        auto merge=[](vector<int>&a,const vector<int>&b){
            for(auto i:b){
                a.push_back(i);
            }
        };
        for(;;){
            if(h.empty()){
                break;
            }
            vector<int> t;
            for(auto i:h){
                ans.push_back(i);
                for(auto j:graph[i]){
                    if(!timestamp[j]){
                        timestamp[j]=timestamp[i]+1;
                    }else if(timestamp[i]+1>timestamp[j]){ /*@WRONG*/
                        return {};
                    }
                }
                merge(t,graph[i]);
            }
            t.swap(h);
        }
        return ans;
    }
};

//6
//[[1,0],[2,1],[3,2],[4,3],[5,4],[2,5]]
//2
//[]
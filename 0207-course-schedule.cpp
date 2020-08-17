//
// Created by Steve on 8/4/2020.
//

#include "solver.h"

class Solution {
public:
#define BOUNDARY_CHECK(n,v) \
do{\
    if(n<2||v.size()<2){\
        return true;\
    }\
}while(0)
#define GENERATE_GRAPH(v,graph,head) \
do{\
    decltype(head) tail,t;\
    for(auto&i:v){\
        head.insert(i[0]),tail.insert(i[1]);\
        graph.insert({i[0],i[1]});\
    }\
    t=head;\
    for(auto&i:t){\
        if(tail.count(i)){\
            head.erase(i);\
        }\
    }\
    if(head.empty()){\
        return false;\
    }\
}while(0)
    bool canFinish_DFS(int numCourses, vector<vector<int>>& prerequisites){
        unordered_multimap<int,int> graph;
        unordered_set<int> head,path;
        vector<bool> mark(numCourses+1,false);
        BOUNDARY_CHECK(numCourses,prerequisites);
        GENERATE_GRAPH(prerequisites,graph,head);
        function<bool(int)> dfs;
        int count=0;
        dfs=[&graph,&mark,&path,&count,&dfs](int u)->bool{
            if(path.count(u)){
                return false;
            }
            if(mark[u]||!graph.count(u)){
                return (mark[u]=true);
            }
            mark[u]=true;
            path.insert(u);
            auto range=graph.equal_range(u);
            for(auto edge=range.first;edge!=range.second;++edge){
                if(!dfs(edge->second)){
                    return false;
                }
                ++count;
            }
            path.erase(u);
//            graph.erase(u); /*cause iterator invalid*/
            return true;
        };
        for(auto&i:head){
            graph.insert({numCourses,i});
        }
        if(!dfs(numCourses)){
            return false;
        }
        return graph.size()==count;
    }

    bool canFinish_DFS_V2(int numCourses,vector<vector<int>>&prerequisites){
#define PREDECESSOR 0
#define SUCCESSOR 1
        if(prerequisites.empty()){
            return true;
        }
        enum class Status:char{
            UNTRACED,
            TRACING,
            TRACED,
        };
        vector<Status> status(numCourses, Status::UNTRACED); //act as PATH & MARK
        vector<vector<int>> reverse_adjacent(numCourses); //same as adjacent
        for(auto&i:prerequisites){
            reverse_adjacent[i[SUCCESSOR]].push_back(i[PREDECESSOR]);
        }
        function<bool(int)> dfs; //ring check
        dfs=[&status,&reverse_adjacent,&dfs](int v)->bool{
            switch (status[v]) {
                case Status::TRACED:
                    return false;
                case Status::TRACING:
                    return true;
                default:{
                    status[v]=Status::TRACING;
                    for(auto&u:reverse_adjacent[v]){
                        if(dfs(u)){
                            return true;
                        }
                    }
                    status[v]=Status::TRACED;
                    return false;
                }
            }
        };
        while(numCourses--){
            if(dfs(numCourses)){
                return false;
            }
        }
        return true;
    }

    bool canFinish_TOPOLOGY_SORT(int numCourses,vector<vector<int>>&prerequisites){
        if(prerequisites.empty()){
            return true;
        }
        vector<int> rank(numCourses,0);
        vector<vector<int>> adjacent(numCourses);
        int count=0;
        queue<int> queue;
        for(auto&i:prerequisites){
            ++rank[i[1]];
            adjacent[i[0]].push_back(i[1]);
        }
        for(auto&i:rank){
            if(!i){
                queue.push(&i-&rank[0]);
            }
        }
        while(!queue.empty()){
            auto u=queue.front();
            queue.pop();
            for(auto&v:adjacent[u]){
                if(--rank[v]==0){
                    queue.push(v);
                }
            }
            count+=adjacent[u].size(); //or ++count;
        }
        return count==prerequisites.size(); //or return count==numCourses;
    }

    //multimap is slower
    bool canFinish_TOPOLOGY_SORT_V2(int numCourses,vector<vector<int>>&prerequisites){
        BOUNDARY_CHECK(numCourses,prerequisites);
        unordered_multimap<int,int> graph;
        unordered_set<int> head;
        vector<int> rank(numCourses,0);
        GENERATE_GRAPH(prerequisites,graph,head);
        int count=0;
        queue<int> queue;
        for(auto&i:prerequisites){
            ++rank[i[1]];
        }
//        for(auto&i:rank){
//            if(!i){
//                queue.push(&i-&rank[0]);
//            }
//        }
        for(auto&i:head){
            queue.push(i);
        }
        while(!queue.empty()){
            auto u=queue.front();
            queue.pop();
            auto range=graph.equal_range(u);
            for(auto edge=range.first;edge!=range.second;++edge){
                auto&v=edge->second;
                if(--rank[v]==0){
                    queue.push(v);
                }
                ++count;
            }
        }
        return count==prerequisites.size();
    }

    bool canFinish(int numCourses,vector<vector<int>>&prerequisites){
        return canFinish_DFS_V2(numCourses,prerequisites);
    }

    /** TOPOLOGY SORT
     * Questions:
     *   1. How to construct a graph?
     *   2. How to find the entry points?
     *   3. How to define a ring?
     */
//    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
//        BOUNDARY_CHECK(numCourses,prerequisites);
//        unordered_multimap<int,int> um;
//        unordered_set<int> head;
//        queue<int> queue;
//        vector<int> rank(numCourses,0);
//        int depth=1;
//        GENERATE_GRAPH(prerequisites,um,head);
//        for(auto&i:head){
//            queue.push(i);
//            rank[i]=depth;
//        }
//        auto remain=um;
//        while(!queue.empty()){
//            int n=queue.size();
//            ++depth;
//            while(n--){
//                int p=queue.front();
//                queue.pop();
//                remain.erase(p);
//                auto range=um.equal_range(p);
//                for(auto it=range.first;it!=range.second;++it) {
//                    auto&k=rank[it->second];
//                    if(k){
//                        auto former=um.find(it->second);
//                        if(former!=um.end()){
//                            auto q=former->second;
//                            if(rank[q]&&(rank[q]+1<depth||q==p)){
//                                return false;
//                            }
//                        }
//                    }else{
//                        k=depth;
//                        queue.push(it->second);
//                    }
//                }
//            }
//        }
//        return remain.empty();
//    }
};

MAIN(){
#define TEST1 3,(data={{1,0},{2,0}})
#define TEST2 8,(data={{1,0},{2,6},{1,7},{5,1},{6,4},{7,0},{0,5}})
#define TEST3 3,(data={{0,2},{1,2},{2,0}})
#define TEST(x,e) EXPECT(solver.canFinish(TEST##x),e)
    vector<vector<int>> data;
    Solution solver;
    TEST(1,1);
    TEST(2,0);
    TEST(3,0);
}
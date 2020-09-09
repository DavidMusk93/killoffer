//
// Created by Steve on 9/7/2020.
//

#include "solver_ex.h"

class Solution {
public:
    bool adjacent(const string&p,const string&q){
        const int N=p.size();
        int delta={};
        for(int i=0;i<N;++i){
            if(p[i]!=q[i]&&delta++==1){
                return false;
            }
        }
        return delta==1;
    }
    inline unsigned int qhash(const string&s){
        const char*p=s.c_str();
        unsigned int h{};
        char c;
        while((c=*p++)){
            h=(h<<5U)-h+c;
        }
        return h;
    }
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
#define NODE_TYPE unsigned int
#define PATH_START h1
#define PATH_END h2
//        auto hash=std::hash<string>{};
        auto hash=[this](const string&s){return qhash(s);}; /*@PRIME-4 replace string with int(hash)*/
        unordered_map<string,NODE_TYPE> table;
        for(auto&s:wordList){
            table[s]=hash(s);
        }
        auto h1=hash(beginWord),h2=hash(endWord);
//        unordered_multimap<string,string> graph;
        unordered_map<NODE_TYPE,vector<NODE_TYPE>> graph; /*@PRIME-3 avoid using unordered_multimap*/
//        if(std::none_of(wordList.begin(),wordList.end(),[&PATH_END,&table](auto&s){return table[s]==PATH_END;})){
//            return false;
//        }
//        if(std::none_of(wordList.begin(),wordList.end(),[&PATH_START,&table](auto&s){return table[s]==PATH_START;})){
//            wordList.push_back(beginWord);
//        }
        if(table.count(endWord)==0){
            return false;
        }
        if(table.count(beginWord)==0){
            table[beginWord]=h1; /*@NOTICE*/
            wordList.push_back(beginWord);
        }
        const int N=wordList.size();
        for(int i=0;i<N;++i){
            for(int j=i+1;j<N;++j){
                auto&p=wordList[i];
                auto&q=wordList[j];
                if(adjacent(p,q)){
//                    graph.insert({p,q});
//                    graph.insert({q,p});
                    auto hp=table[p],hq=table[q];
                    graph[hp].push_back(hq);
                    graph[hq].push_back(hp);
                }
            }
        }
//        for(auto&pair:graph){
//            cout<<pair.first<<","<<pair.second<<endl;
//        }
//        unordered_map<NODE_TYPE,int> to; /*@PRIME-6 distance table is redundant*/
//        to[PATH_START]=1;
        queue<NODE_TYPE> queue;
//        unordered_set<string> trace; /*@PRIME-1 erase rather than record*/
        queue.push(PATH_START);
        int depth=1;
        while(!queue.empty()){
            auto n=queue.size();
            ++depth;
            while(n--){ /*PEEL ONION*/
                auto s=queue.front();
                queue.pop();
//            if(s==endWord){
//                continue;
//            }
//            trace.insert(s);
//            auto pair=graph.equal_range(s);
//            for(auto it=pair.first;it!=pair.second;++it){
////                if(trace.count(it->second)){
////                    continue;
////                }
//                queue.push(it->second);
//                auto k=to[it->first]+1;
//                auto&a=to[it->second];
//                a=a?min(a,k):k;
////                LOG("%s:%d",it->second.c_str(),a);
//                if(it->second==endWord){ /*@PRIME-2 return on touching*/
//                    return a;
//                }
//            }
                auto&dist=graph[s];
//                auto k=to[s]+1;
                for(auto&d:dist){
                    if(graph[d].empty()){ /*@PRIME-5 minimize enqueue & dequeue*/
                        continue;
                    }
                    queue.push(d);
//                    auto&a=to[d];
//                    a=a?min(a,k):k;
                    if(d==PATH_END){
                        return depth;
                    }
                }
//            graph.erase(s);
                dist.clear();
            }
        }
//        return to[endWord];
        return 0;
    }
    int v2(string beginWord,string endWord,vector<string>&wordList){
        if(none_of(wordList.begin(),wordList.end(),[&endWord](auto&s){return s==endWord;})){
            return 0;
        }
        const int N=beginWord.size();
        auto adj=[&N](const string&p,const string&q){
            int d{};
            for(int i=0;i<N;++i){
                if(p[i]!=q[i]&&d++==1){
                    return false;
                }
            }
            return d==1;
        };
        function<void(vector<string>&,vector<string>&)> op;
        int ans{1};
        op=[&op,&adj,&ans,&endWord](vector<string>&from,vector<string>&to){
            vector<string> v1,v2;
            ++ans;
            const int N=to.size();
            int k=0;
            for(auto&p:from){
//                for(auto&q:to){ /*@PRIME-1 move empty string to list head*/
//                    if(!q.empty()&&adj(p,q)){
//                        if(q==endWord){
//                            throw ans;
//                        }
//                        v1.push_back(std::move(q));
//                    }
//                }
                for(int i=k;i<N;++i){
                    auto&q=to[i];
                    if(adj(p,q)){
                        if(q==endWord){
                            throw ans;
                        }
                        v1.push_back(std::move(q));
                        swap(to[k++],q);
                    }
                }
            }
//            for(auto&s:to){
//                if(!s.empty()){
//                    v2.push_back(std::move(s));
//                }
//            }
            for(int i=k;i<N;++i){
                v2.push_back(std::move(to[i]));
            }
            if(v1.empty()||v2.empty()){
                throw 0;
            }
            from.swap(v1),to.swap(v2);
            op(from,to); /*tail recursion optimization*/
        };
        vector<string> from{beginWord};
        try{
            op(from,wordList);
        }catch(int&n){
            return n;
        }
        return 0;
    }
};

MAIN(){
    PREREQUISITES(v2);
    vector<string> list;
    list={"hot","dot","dog","lot","log","cog"};
    TEST(5,"hit","cog",list);
    list={"hot","dot","dog","lot","log"};
    TEST(0,"hit","cog",list);
}
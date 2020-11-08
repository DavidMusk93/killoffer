//
// Created by Steve on 9/25/2020.
//

#include "solver_ex.h"

class Solution {
public:
//    struct Edge{
//        enum class Type:char{
//            LEFT,
//            RIGHT,
//        };
//        Type type;
//        vector<int>&ref;
//    };
    struct Edge{
        int x,y;
        bool operator<(const Edge&e) const{
            return x<e.x||(x==e.x&&y<e.y);
        }
    };

    static void bubble(vector<Edge>&edges,Edge e){ /*not so fast*/
        edges.push_back(e);
        const int N=edges.size();
        for(int i=N-1;i>0;--i){
            auto&p=edges[i];
            auto&q=edges[i-1];
            if(p.x>q.x||(p.x==q.x&&p.y>=q.y/**/)){
                break;
            }
            swap(p,q);
        }
    }

    vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
        multiset<Edge> edges;
        for(auto&v:buildings){
            edges.insert({v[0],-v[2]});
            edges.insert({v[1],v[2]});
        }
        vector<vector<int>> ans;
        multiset<int> hs{0};
        int pre=0;
        for(auto&e:edges){
            if(e.y<0){
                hs.insert(-e.y);
            }else{
                hs.erase(hs.find(e.y));
            }
            auto cur=*hs.rbegin();
            if(pre!=cur){ /*previous maximum height not equal to current*/
                ans.push_back({e.x,cur});
            }
            pre=cur;
        }
        return ans;
    }
    vector<vector<int>> v2(vector<vector<int>>&buildings){
        if(buildings.empty()){
            return {};
        }
        vector<Edge> edges;
        vector<vector<int>> t;
        int N=buildings.size();
        t.push_back(std::move(buildings[0]));
        for(int i=1;i<N;++i){ /*avoid busy bubble*/
            auto&p=t.back();
            auto&q=buildings[i];
            if(p[1]==q[1]&&p[2]>=q[2]){
                continue;
            }
            t.push_back(std::move(q));
        }
        buildings.swap(t);
        N=buildings.size();
        edges.reserve(N*2);
        for(auto&v:buildings){
            bubble(edges,{v[0],-v[2]});
            bubble(edges,{v[1],v[2]});
        }
        vector<vector<int>> ans;
        multiset<int> hs{0};
        int pre=0;
        for(auto&e:edges){
            if(e.y<0){
                hs.insert(-e.y);
            }else{
                hs.erase(hs.find(e.y));
            }
            auto cur=*hs.rbegin();
            if(pre!=cur){
                ans.push_back({e.x,cur});
            }
            pre=cur;
        }
        return ans;
    }
};

ostream&operator<<(ostream&os,const Solution::Edge&e){
    os<<"{"<<e.x<<","<<e.y<<"}";
    return os;
}

MAIN(){
    PREREQUISITES(getSkyline);
    vector<vector<int>> buildings={{2,7,7},{2,9,10},{3,7,15},{5,12,12},{15,20,10},{19,24,8}};
    cout<<INVOKE(buildings)<<endl;
}

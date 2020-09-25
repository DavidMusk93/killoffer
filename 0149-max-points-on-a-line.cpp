//
// Created by Steve on 9/15/2020.
//

#include "solver_ex.h"

class Solution {
    using u32=unsigned int;
    using u64=unsigned long;
#define U64FROM2U32(x,y) (static_cast<u64>(x)<<32U)+static_cast<u32>(y)
public:
    u64 gcdex(int i,int j){
//        if(!i&&!j){ /*assume no duplicate points*/
//            return 0;
//        }
        if(!i){
            return static_cast<u32>(j);
        }
        if(!j){
            return static_cast<u64>(i)<<32U;
        }
        auto a=i,b=j;
        i=abs(i),j=abs(j);
        if(i==j){
            return U64FROM2U32(a>0?1:-1,b>0?1:-1);
        }
        int p=__builtin_ctz(i);
        int q=__builtin_ctz(j);
        i>>=p,j>>=q;
        do{
            if(i==j){
                break;
            }
            if(i<j){
                swap(i,j);
            }
            j=i-j;
            for(;!(j&1);j>>=1);
        }while(i!=j);
        auto k=j*(1<<(p<q?p:q));
        return U64FROM2U32(a/k,b/k);
    }
    int maxPoints(vector<vector<int>>& points) {
        const int N=points.size();
        if(N<2){
            return N;
        }
        unordered_map<u64,int> map;
        for(int i=0;i<N;++i){
            for(int j=i+1;j<N;++j){
                ++map[gcdex(points[i][0]-points[j][0],points[i][1]-points[j][1])];
            }
        }
        int ans{};
        for(auto&p:map){
            ans=max(ans,p.second);
        }
//        LOG("ans,%d",ans);
        return int(sqrt(ans*2))+1;
    }

    int v2(vector<vector<int>>&points){
#define X(_p) _p[0]
#define Y(_p) _p[1]
#define DX(_1,_2) (X(_1)-X(_2))
#define DY(_1,_2) (Y(_1)-Y(_2))
        const int N=points.size();
        if(N<3){
            return N;
        }
        int ans=0;
        for(int i=0;i<N;++i){
            int dup=1; /*count i itself*/
            for(int j=i+1;j<N;++j){
                int count{};
                if(points[i]==points[j]){++dup;}
                else{
                    count=1; /*count j*/
                    /*int*/long dx=DX(points[i],points[j]);
                    long dy=DY(points[i],points[j]);
                    for(int k=j+1;k<N;++k){
                        if(dx*DY(points[i],points[k])==dy*DX(points[i],points[k])){++count;} /*may overflow for int*/
                    }
                }
                ans=max(ans,count+dup);
            }
            if(ans>N/2){
                return ans;
            }
        }
        return ans;
    }
};

MAIN(){
    PREREQUISITES(v2);
    vector<vector<int>> points;
    points={{1,1},{3,2},{5,3},{4,1},{2,3},{1,4}};
    TEST(4,points);
    points={{1,1},{2,2},{3,3}};
    TEST(3,points);
    points={{0,0},{1,1},{1,-1}};
    TEST(2,points);
    points={{1,1},{1,1},{1,1}};
    TEST(3,points);
}
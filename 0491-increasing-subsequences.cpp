//
// Created by Steve on 8/25/2020.
//

#include "solver_ex.h"

class Solution {
public:
    struct Pusher{
        using Pred=std::function<bool()>;
        Pusher(vector<int>&seq,int k,const Pred&pred):seq(seq),flag(false){
            flag=pred();
            if(flag){
                seq.push_back(k);
            }
        }
        ~Pusher(){
            if(flag){
                seq.pop_back();
            }
        }
        vector<int>&seq;
        bool flag;
    };
    struct VectorView{
        VectorView(vector<int>&nums,int s,int e):nums(nums),s(s),e(e){}
        bool find(int target){
            for(int i=s;i<e;++i){
                if(nums[i]==target){
                    return true;
                }
            }
            return false;
        }
        vector<int>&nums;
        int s,e;
    };
    vector<vector<int>> findSubsequences(vector<int>&nums){
        return findSubsequences_v3(nums);
    }
    vector<vector<int>> findSubsequences_v1(vector<int>& nums) {
        vector<vector<int>> ans;
        ans.reserve(32);
        const int N=nums.size();
        if(N<2){
            return {};
        }
        function<void(int,vector<int>&)> dfs;
        dfs=[&dfs,&nums,&N,&ans](int i,vector<int>&seq){
            if(i==N){
                return;
            }
            for(int j=i;j<N;++j){
                if(j>i&&(nums[j-1]==nums[j])){
                    continue;
                }
                if(seq.empty()&&VectorView{nums,0,j}.find(nums[j])){
                    break;
                }
                if(seq.empty()||nums[j]>=seq.back()){
                    seq.push_back(nums[j]);
                    dfs(j+1,seq);
                    if(seq.size()>1){
                        ans.push_back(seq);
                    }
                    seq.pop_back();
                }
//                Pusher pusher{seq,nums[j],[&seq,k=nums[j]/*move capture*/](){return seq.empty()||k>=seq.back();}};
//                if(pusher.flag/*push success*/){
//                    dfs(j+1,seq);
//                    if(seq.size()>1){
//                        ans.push_back(seq);
//                    }
//                }
            }
        };
        vector<int> seq;
        dfs(0,seq);
        return ans;
    }
    vector<vector<int>> findSubsequences_v2(vector<int>&nums){
        const int N=nums.size();
        if(N<2){
            return {};
        }
        set/*not unordered_set*/<vector<int>> ans;
        vector<int> seq;
        function<void(vector<int>&,int)> dfs;
        dfs=[&dfs,&nums,&N,&ans](vector<int>&seq,int i){
            if(i==N){
                return;
            }
            for(int j=i;j<N;++j){
                int n=seq.size();
                int k=nums[j];
                if((n&&k<seq.back())||(j>i&&k==nums[j-1])){
                    continue;
                }
                seq.push_back(k);
                if(n){
                    ans.insert(seq);
                }
                dfs(seq,j+1);
                seq.pop_back();
            }
        };
        dfs(seq,0);
        return vector<vector<int>>{ans.begin(),ans.end()};
    }
    vector<vector<int>> findSubsequences_v3(vector<int>&nums){
#define S32_MIN 0x80000000
        const int N=nums.size();
        if(N<2){
            return {};
        }
        vector<vector<int>> ans;
        vector<int> seq;
        function<void(int,int)> dfs;
        dfs=[&dfs,&nums,&N,&ans,&seq](int i,int last){
            if(i==N){
                if(seq.size()>1){
                    ans.push_back(seq);
                }
                return;
            }
            auto k=nums[i];
            /*choose this*/
            if(k>=last){
                seq.push_back(k);
                dfs(i+1,k);
                seq.pop_back();
            }
            /*abandon this*/
            if(k!=last){
                dfs(i+1,last);
            }
        };
        dfs(0,S32_MIN);
        return ans;
    }
};

MAIN(){
    PREREQUISITES(findSubsequences);
    vector<int> v1{10,9,8,9,10};
    vector<int> v2{1,4,6,7,7,7,1,1,1};
    vector<int> v3{-100,-100,0,0,0,100,100,0,0};
    for(auto&v:INVOKE(v3)){
        cout<<v;
    }
}
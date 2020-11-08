//
// Created by Steve on 10/22/2020.
//

#include "solver_ex.h"

class Node{
public:
    Node(int key,Node*pLeft,Node*pRight):key_(key),lessThanCount_(0),duplicateCount_(1),pLeft_(pLeft),pRight_(pRight){}
    Node(int key):Node(key,nullptr,nullptr){}
    int insert(int key){
        if(key<key_){
            ++lessThanCount_;
            if(!pLeft_){
                pLeft_=new Node(key);
                return 0;
            }
            return pLeft_->insert(key);
        }else if(key>key_){
            if(!pRight_){
                pRight_=new Node(key);
                return lessThanCount_+duplicateCount_;
            }
            return lessThanCount_+duplicateCount_+pRight_->insert(key);
        }
        ++duplicateCount_;
        return lessThanCount_;
    }
private:
    int key_;
    int lessThanCount_,duplicateCount_;
    Node*pLeft_,*pRight_;
};

class BST{
public:
    struct Node{
    public:
        Node(int k):k_(k),c1_(0),c2_(0),p_{},q_{}{}
        int insert(int k,deque<BST::Node>&alloc){
            if(k==k_){
                ++c2_;
                return c1_;
            }else if(k<k_){
                ++c1_;
                if(!p_){
                    alloc.push_back({k});
                    p_=&alloc.back();
                }
                return p_->insert(k,alloc);
            }
            if(!q_){
                alloc.push_back({k});
                q_=&alloc.back();
            }
            return c1_+c2_+q_->insert(k,alloc);
        }
        int get(){return k_;}
    private:
        int k_,c1_,c2_;
        Node*p_,*q_;
    };

    BST(BST::Node*root):root_(root){
        root_->insert(root_->get(),data_); /*self count*/
    }
    int insert(int k){
        return root_->insert(k,data_);
    }

private:
    BST::Node*root_;
    deque<BST::Node> data_;
};

class Solution {
public:
#define PREDEFINE(N,ans) \
const int N=nums.size();\
if(!N){return {};}\
vector<int> ans(N);
    vector<int> countSmaller(vector<int>& nums) {
        const int N=nums.size();
        if(!N){
            return {};
        }
        vector<int> ans(N);
        set<int> set; /*does not count duplicates*/
        for(int i=N-1;i>=0;--i){
            const auto [it,_]=set.insert(nums[i]);
//            auto p=set.insert(nums[i]);
            ans[i]=distance(set.begin(),it);
        }
        return ans;
    }
    vector<int> v2(vector<int>&nums){
        const int N=nums.size();
        if(!N){
            return {};
        }
        vector<int> ans(N);
        set<pair<int,int>> set;
        for(int i=N-1;i>=0;--i){
            const auto [it,success]=set.insert({nums[i],0});
            for(int j=1;!success;++j){
                auto p=set.insert({nums[i],j});
                if(p.second){
                    break;
                }
            }
            ans[i]=distance(set.begin(),it);
        }
        return ans;
    }
    vector<int> v3(vector<int>&nums){
        const int N=nums.size();
        if(!N){
            return {};
        }
        vector<int> ans(N);
        Node root(nums[N-1]);
        for(int i=N-2;i>=0;--i){
            ans[i]=root.insert(nums[i]);
        }
        return ans;
    }
    vector<int> v4(vector<int>&nums){
        PREDEFINE(N,ans);
        BST::Node node{nums[N-1]};
        BST bst{&node};
        for(int i=N-2;i>=0;--i){
            ans[i]=bst.insert(nums[i]);
        }
        return ans;
    }
};

MAIN(){
    PREREQUISITES(v4);
    vector<int> v1,v2;
    v1={5,2,6,1};
    v2={2,1,1,0};
    TEST(v2,v1);
    v1={26,78,27,100,33,67,90,23,66,5,38,7,35,23,52,22,83,51,98,69,81,32,78,28,94,13,2,97,3,76,99,51,9,21,84,66,65,36,100,41};
    v2={10,27,10,35,12,22,28,8,19,2,12,2,9,6,12,5,17,9,19,12,14,6,12,5,12,3,0,10,0,7,8,4,0,0,4,3,2,0,1,0};
    TEST(v2,v1);
}

//
// Created by Steve on 2/11/2021.
//

#include "solver_ex.h"

class KTH{
public:
    KTH(int k):k_(k){}
    void put(int i){
        if(p_.size()<k_){
            p_.push(i);
        }else if(p_.top()<i){ // great than kth
//            q_.push(p_.top());
            p_.pop();
            p_.push(i);
        }/*else{ // no great than kth
            q_.push(i);
        }*/
    }
    int get(){
        return p_.top(); // danger
    }
private:
    int k_;
    priority_queue<int,deque<int>,greater<>> p_; // minimal heap
//    priority_queue<int> q_; // maximum heap
};

#define MAXVAL 10000
static int _a[MAXVAL*2+1];
static int*a=&_a[MAXVAL];

// Why need optimization?
class V2{
public:
    V2(int k,vector<int>&nums):k_(k),p_{}{
        for(auto&i:_a){
            i=0;
        }
        for(auto i:nums){
            ++a[i];
        }
    }
    int add(int val){
        if(!p_){
            ++a[val];
            for(int i=MAXVAL,k=k_;;--i){
                if(a[i]>=k){
                    a[i]=k;
                    p_=&a[i];
                    break;
                }
                k-=a[i];
            }
        }else if(val>int(p_-a)){
            ++a[val];
            if(!--*p_){
                for(++p_;!*p_;++p_){}
            }
        }
        return int(p_-a);
    }

private:
    int k_;
    int*p_;
};

class KthLargest {
public:
    KthLargest(int k, vector<int>& nums) {
        handler_.reset(new V2(k,nums));
    }

    int add(int val) {
        return handler_->add(val);
    }

private:
    unique_ptr<V2> handler_;
};
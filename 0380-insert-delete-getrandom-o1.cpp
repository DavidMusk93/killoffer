//
// Created by Steve on 9/11/2020.
//

#include "solver_ex.h"

class RandomizedSet {
public:
    /** Initialize your data structure here. */
    RandomizedSet() {
        srand(time(nullptr));
    }

    /** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
    bool insert(int val) {
        return set_.insert(val).second;
    }

    /** Removes a value from the set. Returns true if the set contained the specified element. */
    bool remove(int val) {
        return set_.erase(val);
    }

    /** Get a random element from the set. */
    int getRandom() {
        auto n=rand()%(set_.size());
        int i=0;
        for(auto&p:set_){
            if(i++==n){
                return p;
            }
        }
        return -1;
    }
    unordered_set<int> set_;
};

namespace sun{
class RandomizedSet{
public:
    RandomizedSet(){
        srand(time(nullptr));
    }
    bool insert(int val){
        if(map_.count(val)){
            return false;
        }
        data_.push_back(val);
        map_.insert({val,data_.size()});
        return true;
    }
    bool remove(int val){
        if(map_.count(val)){
            auto i=map_[val];
            if(i!=data_.size()){ /*not the last*/
                auto tail=data_.back();
                map_[tail]=i;
                swap(data_[i-1],data_.back());
            }
            map_.erase(val);
            data_.pop_back();
            return true;
        }
        return false;
    }
    int getRandom(){
        auto n=rand()%data_.size();
        return data_[n];
    }

private:
    vector<int> data_;
    unordered_map<int, int> map_;
};
}

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */

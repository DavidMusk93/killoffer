//
// Created by Steve on 6/29/2020.
//

#include <map>

class LRUCache {
public:
    LRUCache(int capacity) : capacity_(capacity), timestamp_(0) {

    }

    int get(int key) {
        if (m1_.find(key) != m1_.end()) {
            auto &item = m1_[key];
            m2_.erase(item.ts);
            item.ts = ++timestamp_;
            m2_[timestamp_] = key;
            return item.val;
        }
        return -1;
    }

    void put(int key, int value) {
        if (m1_.find(key) != m1_.end()) {
            auto &item = m1_[key];
            m2_.erase(item.ts);
            item.ts = ++timestamp_;
            m2_[timestamp_] = key;
            item.val = value;
        } else if (m1_.size() < capacity_) {
            m1_[key] = Item{value, ++timestamp_};
            m2_[timestamp_] = key;
        } else {
            auto k = m2_.begin()->second;
            m2_.erase(m2_.begin());
            m1_.erase(k);
            put(key, value);
        }
    }

private:
    int capacity_;
    size_t timestamp_;
    struct Item {
        int val;
        size_t ts;
    };
    std::map<int, Item> m1_;
    std::map<size_t, int> m2_;
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
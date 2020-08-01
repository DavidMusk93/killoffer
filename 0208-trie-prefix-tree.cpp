//
// Created by Steve on 7/13/2020.
//

#include <string>
#include <memory>
#include <utility>

#include "common.h"

using namespace std;

class Trie {
#define INDEX(x) (x[0]-'a')
public:
    /** Initialize your data structure here. */
    Trie() : Trie("") {}

    Trie(std::string prefix) : valid_(true), prefix_(std::move(prefix)) {}

    /** Inserts a word into the trie. */
    void insert(string word) {
        if (word.empty()) {
            return;
        }
        int i = 0, n1 = prefix_.size(), n2 = word.size(), delta;
        for (; i < n1 && i < n2 && word[i] == prefix_[i]; ++i);
        if (i == n1) {
            auto left = word.substr(i);
            if (left.empty()) { //equal
                valid_=true;
                return;
            }
            delta = INDEX(left);
            if (list_[delta]) {
                list_[delta]->insert(left);
            } else {
                list_[delta] = make_shared<Trie>(left);
            }
        } else {
            auto l1 = prefix_.substr(i);
            auto l2 = word.substr(i);
            auto node = make_shared<Trie>(l1);
            swap(list_, node->list_);
            prefix_ = prefix_.substr(0, i);
            delta = INDEX(l1);
            list_[delta] = node;
            if (!l2.empty()) { //intersect
                valid_=false;
                delta = INDEX(l2);
                list_[delta] = make_shared<Trie>(l2);
            }
        }
    }

    /** Returns if the word is in the trie. */
    bool search(string word) {
        if (!polyfill::string(word).starts_with(prefix_)) {
            return false;
        }
        auto left = word.substr(prefix_.size());
        if (left.empty()) {
            return valid_;
        }
        int delta = INDEX(left);
        if (list_[delta]) {
            return list_[delta]->search(left);
        }
        return false;
    }

    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        auto ps = polyfill::string(prefix_);
        if (ps.starts_with(prefix)) {
            return true;
        }
        if (ps.n == prefix_.size()) {
            auto left = prefix.substr(ps.n);
            int delta = INDEX(left);
            if (list_[delta]) {
                return list_[delta]->startsWith(left);
            }
        }
        return false;
    }

private:
    bool valid_;
    string prefix_;
    shared_ptr<Trie> list_[26];
#undef INDEX
};

#include "macro.h"

MAIN(){
    string s1{"abc"};
    string s2{""};
    auto ps=polyfill::string(s1);
    int res=ps.starts_with(s2);
    LOG("'%s' starts with '%s': %s(%d)",s1.c_str(),s2.c_str(),res?"true":"false",ps.n);
}
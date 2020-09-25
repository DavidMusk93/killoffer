//
// Created by Steve on 9/22/2020.
//

#ifndef KILLOFFER_TRIE_H
#define KILLOFFER_TRIE_H

//#include <vector>
#include <deque>
#include <string>

class TrieIf{
public:
    virtual TrieIf*getchild(char c)=0;
    virtual bool isword()=0;
};

class TrieImpl:public TrieIf{
public:
    TrieImpl():isword_(false),children_{}{}

    void insert(const std::string&s,std::deque<TrieImpl>&alloc){
        TrieImpl*p=this;
        for(auto c:s){
            int i=c-'a';
            if(!p->children_[i]){
                alloc.emplace_back();
                p->children_[i]=&alloc.back();
            }
            p=p->children_[i];
        }
        p->isword_=true;
    }
    bool search(const std::string&s){
        TrieImpl*p{};
        if(!startsWith(s,&p)){
            return false;
        }
        return p->isword_;
    }
    bool startsWith(const std::string&s,TrieImpl**tailptr){
        if(s.empty()){
            return false;
        }
        TrieImpl*p=this;
        for(auto c:s){
            int i=c-'a';
            if(!p->children_[i]){
                return false;
            }
            p=p->children_[i];
        }
        if(tailptr){*tailptr=p;}
        return true;
    }

    TrieIf*getchild(char c) override{
        return children_[c-'a'];
    }

    bool isword() override{
        return isword_;
    }

private:
//    char c_;
    bool isword_;
    TrieImpl*children_[26];
};

class Trie{
public:
    Trie(){
//        alloc_.reserve(128);
        alloc_.emplace_back();
        root_=&alloc_.back();
    }

    void insert(const std::string&s){
        root_->insert(s,alloc_);
    }
    bool search(const std::string&s){
        return root_->search(s);
    }
    bool startsWith(const std::string&s){
        return root_->startsWith(s,nullptr);
    }

    TrieIf*getroot(){
        return root_;
    }
private:
    TrieImpl*root_;
//    std::vector<TrieImpl> alloc_; /*@NOTICE vector would invalidate iterators on resizing*/
    std::deque<TrieImpl> alloc_;
};

#endif //KILLOFFER_TRIE_H

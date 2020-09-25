//
// Created by Steve on 9/14/2020.
//

#include "solver_ex.h"

class NestedInteger{
public:
    bool isInteger() const;
    int getInteger() const;
    const vector<NestedInteger>&getList() const;
};

/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * class NestedInteger {
 *   public:
 *     // Return true if this NestedInteger holds a single integer, rather than a nested list.
 *     bool isInteger() const;
 *
 *     // Return the single integer that this NestedInteger holds, if it holds a single integer
 *     // The result is undefined if this NestedInteger holds a nested list
 *     int getInteger() const;
 *
 *     // Return the nested list that this NestedInteger holds, if it holds a nested list
 *     // The result is undefined if this NestedInteger holds a single integer
 *     const vector<NestedInteger> &getList() const;
 * };
 */

class NestedIterator { /*coroutine is better for this*/
public:
    NestedIterator(vector<NestedInteger>&nestedList):list(nestedList),i(0){}
    NestedIterator(const vector<NestedInteger> &nestedList):list(nestedList),i(0){}

    int next() {
//        if(iterator&&iterator->hasNext()){
//            return iterator->next();
//        }
//        if(list[i].isInteger()){
//            return list[i++].getInteger();
//        }
//        iterator.reset(new NestedIterator(list[i++].getList()));
//        return next();
        return n; /*@PRIME-1 `hasNext` do the real search*/
    }

    bool hasNext() { /*@NOTICE recursion is needed*/
        if(iterator&&iterator->hasNext()){
            n=iterator->next();
            return true;
        }
        if(i<list.size()){
            if(list[i].isInteger()){
                n=list[i++].getInteger();
                return true;
            }
            iterator.reset(new NestedIterator(list[i++].getList()));
            return hasNext();
        }
        return false;
    }
    const vector<NestedInteger>&list;
    int i,n{};
    unique_ptr<NestedIterator> iterator;
};

/**
 * Your NestedIterator object will be instantiated and called as such:
 * NestedIterator i(nestedList);
 * while (i.hasNext()) cout << i.next();
 */
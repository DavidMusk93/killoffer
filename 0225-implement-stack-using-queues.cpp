//
// Created by Steve on 11/12/2020.
//

#include "solver_ex.h"

class MyStack {
public:
    /** Initialize your data structure here. */
    MyStack() {

    }

    /** Push element x to the back of queue. */
    void push(int x) {
        a_=x;
        x_.push_back(x);
    }

    /** Removes the element from in front of queue and returns that element. */
    int pop() {
        int n=x_.size(),a;
        while(--n){
            a_=x_.front();
            y_.push_back(a_);
            x_.pop_front();
        }
        a=x_.front();
        x_.clear();
        x_.swap(y_);
        return a;
    }

    /** Get the front element. */
    int top() {
        return a_;
    }

    /** Returns whether the queue is empty. */
    bool empty() {
        return x_.empty();
    }

private:
    list<int> x_,y_;
    int a_;
};
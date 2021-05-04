//
// Created by Steve on 11/12/2020.
//

#include "solver_ex.h"

class MyQueue {
public:
    /** Initialize your data structure here. */
    MyQueue() {

    }

    /** Push element x to the back of queue. */
    void push(int x) {
        s1_.push(x);
    }

    /** Removes the element from in front of queue and returns that element. */
    int pop() {
        if(s2_.empty()){
            transfer();
        }
        /*defer is cool*/
        int a=s2_.top();
        s2_.pop();
        return a;
    }

    /** Get the front element. */
    int peek() {
        if(s2_.empty()){
            transfer();
        }
        return s2_.top();
    }

    /** Returns whether the queue is empty. */
    bool empty() {
        return s1_.empty()&&s2_.empty();
    }

private:
    void transfer(){
        while(!s1_.empty()){
            s2_.push(s1_.top());
            s1_.pop();
        }
    }

private:
    stack<int> s1_,s2_;
};
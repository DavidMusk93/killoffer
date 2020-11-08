//
// Created by Steve on 10/14/2020.
//

#include "solver_ex.h"

class MedianFinder {
public:
    /** initialize your data structure here. */
    MedianFinder(){

    }

    /** DETAILS:
     * 1. bq, the less part (big heap);
     * 2. lq, the greater part (little heap);
     * 3. if the middle exists, bq holds it.
     */
    void addNum(int num) {
        if(bq.empty()){
            bq.push(num);
        }/*else if(lq.empty()){
            if(num<bq.top()){
                auto t=bq.top();
                bq.pop();
                bq.push(num);
                num=t;
            }
            lq.push(num);
        }*/else if(bq.size()==lq.size()){
            if(num>lq.top()){
                auto t=lq.top();
                lq.pop();
                lq.push(num);
                num=t;
            }
            bq.push(num);
        }else{
            if(num<bq.top()){
                auto t=bq.top();
                bq.pop();
                bq.push(num);
                num=t;
            }
            lq.push(num);
        }
    }

    double findMedian() {
        if(bq.size()==lq.size()){
            return (bq.top()+lq.top())/2.;
        }
        return bq.top();
    }

//    priority_queue<int,deque<int>,less<int>> bq; /*348 ms*/
    priority_queue<int,vector<int>,less<int>> bq; /*216 ms*/
    priority_queue<int,vector<int>,greater<int>> lq;
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */

MAIN(){
    MedianFinder obj;
    obj.addNum(1);
    obj.addNum(2);
    LOG("%f",obj.findMedian());
    obj.addNum(3);
    LOG("%f",obj.findMedian());
}
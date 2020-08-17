//
// Created by Steve on 8/10/2020.
//

#include "solver.h"

class Solution {
public:
    bool canWinNim(int n) { //PLAYER I
//        if(record.count(n)){
//            return record[n];
//        }
//        auto win=[this](int n)->bool{
//            if(!record.count(n)){
//                record[n]=canWinNim(n);
//            }
//            return record[n];
//        };
//        for(auto&i:{1,2,3}){
//            if(!win(n-i)){ //PLAYER II
//                return true;
//            }
//        }
//        return false;
        return /*n%4*/n&3;
    }

protected:
    static unordered_map<int,bool> record; //memory search
};

unordered_map<int,bool> Solution::record={
        {0,false}, //P position
        {1,true}, //N position
        {2,true},
        {3,true},
        {4,false},
        {5,true},
        {6,true,},
        {7,true},};

MAIN(){
#define TEST(x,e) EXPECT(solver.canWinNim(x),e)
    Solution solver;
    EXPECT(solver.canWinNim(6),true);
    EXPECT(solver.canWinNim(30),true);
    EXPECT(solver.canWinNim(81),true);
    TEST(82,true);
    TEST(83,true);
    TEST(85,true);
}
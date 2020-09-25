//
// Created by Steve on 9/10/2020.
//

#include "solver_ex.h"

class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        const int N=gas.size();
        int diff{},i{};
        for(i=0;i<N;++i){
            gas[i]-=cost[i];
            diff+=gas[i];
        }
        if(diff<0){
            return -1;
        }
        int s1{},s2{}; //,s3{};
        int k1{}/*base point*/; //,k2{}/*backtrace point*/;
//        cout<<gas<<endl;
        do{
            for(i=k1;gas[i]<0;++i){
                s1+=gas[i];
            }
            k1=i;
            for(s2=gas[i++];i<N&&s2>0;s2+=gas[i++]);/*{
                if(*//*!k2&&*//*gas[i]>0){
                    s3=s2;
                    k2=i;
                }
            }*/
//            LOG("%d,%d",s1,s2);
            if(i==N){
                return s1+s2>=0?k1:-1;
            }else{
//                s1+=k2?s3:s2;
                s1+=s2;
                s2=0;
//                k1=k2?:i;
//                k2=0;
                k1=i; /*@PRIME-1 the greatest resistance is at the end*/
            }
        }while(true);
    }
};

MAIN(){
    PREREQUISITES(canCompleteCircuit);
    vector<int> gas,cost;
    gas={1,2,3,4,5};
    cost={3,4,5,1,2};
    TEST(3,gas,cost);
    gas={5,1,2,3,4};
    cost={4,4,1,5,1};
    TEST(4,gas,cost);
    gas={2};
    cost={2};
    TEST(0,gas,cost);
    gas={67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66};
    cost={27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26};
    TEST(74,gas,cost);
}
//
// Created by Steve on 10/11/2020.
//

#include "solver_ex.h"

class Solution {
public:
    static vector<int> primes;

    template<size_t N>
    static void fn(vector<int>&out);

    int countPrimes(int n) {
        if(n<2){
            return 0;
        }
        if(primes.empty()){
            fn<5000000>(primes);
        }
        auto lower=lower_bound(primes.begin(),primes.end(),n);
        return distance(primes.begin(),lower);
    }
};

vector<int> Solution::primes{};

template<size_t N>
void Solution::fn(vector<int> &out) {
    bitset<N+1> flag; /*0 is prime*/
    out.reserve(360*1024);
    for(int i=2;i<N;++i){
        if(!flag.test(i)){
            out.push_back(i);
        }
        for(auto p:out){
            if(p*i>N){break;}
            flag.set(p*i);
            if(i%p==0){break;}
        }
    }
}

MAIN(){
    PREREQUISITES(countPrimes);
    TEST(4,10);
    TEST(0,0);
    TEST(0,1);
}

//MAIN(){
//    Solution::fn<1000>(Solution::primes);
//    cout<<Solution::primes<<","<<Solution::primes.size()<<endl;
//}
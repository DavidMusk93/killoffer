//
// Created by Steve on 8/2/2020.
//

#ifndef KILLOFFER_SOLVER_H
#define KILLOFFER_SOLVER_H

#include <vector>
#include <map>
#include <queue>
#include <type_traits>
#include <unordered_set>
#include <unordered_map>
#include <functional>
#include <chrono>
#include <iostream>
#include <algorithm>
#include <set>
#include <bitset>
#include <memory>
#include <list>
#include <sstream>

#include <cassert>
#include <cstring>
#include <cmath>
#include <cctype>

#include "macro.h"
#include "common.h"
#include "base/tool.h"

using namespace std;

namespace sun{
    long now(){
        return chrono::duration_cast<chrono::microseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count();
    }
}

template<typename T>
static inline/*assemble code replacement(enlarge output)*/ std::ostream&operator<<(std::ostream&os,const std::vector<T>&v){
    os<<'[';
    for(auto&i:v){
        if(&i==&v[0]){
            os<<i;
        }else{
            os<<","<<i;
        }
    }
    os<<']';
//    os<<std::endl;
    return os;
}

static inline std::ostream&operator<<(std::ostream&os,const std::string&s){
    os<<"\""<<s.c_str()/*danger*/<<"\"";
    return os;
}

static inline void dump_blob(const void*data,int len){
    auto p=reinterpret_cast<const unsigned char*>(data);
    for(int i=0;i<len;++i,++p){
        if(i){
            cout<<","<<int(*p);
        }else{
            cout<<int(*p);
        }
    }
    cout<<endl;
}

#define COLOR(x) "\x1B[" #x "m"
#define RED COLOR(31)
#define GREEN COLOR(32)
#define RESET COLOR(0)

#define EXPECT(expr,expected) \
do{\
    auto t1=sun::now();\
    auto r=expr;\
    cout<<#expr "="\
        <<r\
        <<" "\
        <<(r==expected?GREEN "pass":RED "failure")\
        <<RESET " ("\
        <<({auto t2=sun::now();t2-t1;})\
        <<"us)"\
        <<endl;\
}while(0)

#define PREREQUISITES() Solution solver

//#define ENHANCED 1
#if ENHANCED
#undef PREREQUISITES
#define PREREQUISITES(member) \
Solution solver;\
const auto&callable=&Solution::member
#define INVOKE(...) std::invoke(callable,&solver,##__VA_ARGS__)
#define TEST(e,...) EXPECT(INVOKE(__VA_ARGS__),e)
#endif

#endif //KILLOFFER_SOLVER_H

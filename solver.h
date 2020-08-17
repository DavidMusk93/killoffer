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

#include <cstring>

#include "macro.h"
#include "common.h"

using namespace std;

namespace sun{
    long now(){
        return chrono::duration_cast<chrono::microseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count();
    }
}

#define EXPECT(expr,expected) \
do{\
    auto t1=sun::now();\
    cout<<#expr\
        <<" "\
        <<((expr)==expected?"pass":"failure")\
        <<" ("\
        <<({auto t2=sun::now();t2-t1;})\
        <<"us)"\
        <<endl;\
}while(0)

#endif //KILLOFFER_SOLVER_H

//
// Created by Steve on 2/1/2021.
//

#include "solver_ex.h"

class Solution {
public:
    vector<int> fairCandySwap(vector<int> &A, vector<int> &B) {
        int a, b;
        bool swap = false;
        a = b = 0;
        if (A.size() > B.size()) {
            A.swap(B);
            swap = true;
        }
        for (auto i:A) {
            a += i;
        }
        for (auto i:B) {
            b += i;
        }
        a = (b - a) / 2;
        sort(B.begin(), B.end());
        auto it1 = B.begin();
        auto it2 = B.end();
        for (auto i:A) {
            if (binary_search(it1, it2, i + a)) {
                return swap ? vector<int>{i + a, i} : vector<int>{i, i + a};
            }
        }
        return {0, 0};
    }
};

MAIN() {
#define MYTEST() TEST(C,A,B)
    PREREQUISITES(fairCandySwap);
    vector<int> A, B, C;
    A = {1, 1};
    B = {2, 2};
    C = {1, 2};
    MYTEST();
    A = {1, 2};
    B = {2, 3};
    MYTEST();
    A = {2};
    B = {1, 3};
    C = {2, 3};
    MYTEST();
    A = {1, 2, 5};
    B = {2, 4};
    C = {5, 4};
    MYTEST();
    A = {35, 17, 4, 24, 10};
    B = {63, 21};
    C = {24, 21};
    MYTEST();
}

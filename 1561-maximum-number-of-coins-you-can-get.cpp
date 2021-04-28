#include "solver_ex.h"

class Solution {
public:
    int maxCoins(vector<int> &piles) {
        int N = piles.size();
        std::sort(piles.begin(), piles.end());
        auto *p = &piles[0] + N;
        N /= 3;
        int a{};
        while (N--) {
            a += p[-2];
            p -= 2;
        }
        return a;
    }
};

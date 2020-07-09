//
// Created by Steve on 7/2/2020.
//

#include <vector>

using namespace std;

class Solution {
public:
    vector<int> dailyTemperatures(vector<int> &T) {
        vector<int> big(T.size(), -1);
        if (T.size() == 0) {
            return big;
        }
        big.back() = 0;
        int p, q, t;
        for (q = T.size() - 1; q > 0; --q) {
            t = T[q - 1];
            big[q - 1] = 0;
            for (p = q;; p += big[p]) {
                if (T[p] > t) {
                    big[q - 1] = p - q + 1;
                    break;
                }
                if (!big[p]) {
                    break;
                }
            }
        }
        return big;
    }
};

#include "macro.h"

MAIN() {
    vector<int> T{73, 74, 75, 71, 69, 72, 76, 73};
    auto res = Solution().dailyTemperatures(T);
    FORWARD_FOR(i, 0, res.size()) {
        LOG("%d", res[i]);
    }
    return 0;
}
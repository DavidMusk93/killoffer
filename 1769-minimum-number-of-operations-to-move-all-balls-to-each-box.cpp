#include "solver_ex.h"

class Solution {
public:
    vector<int> minOperations(string boxes) {
        int i, j/*ones*/, k/*steps*/, N = boxes.size();
        if (N == 0) {
            return {};
        } else if (N == 1) {
            return {0};
        }
        for (auto &c:boxes) {
            c -= '0';
        }
        vector<int> ans(N);
#define FORWARD(__init, __cond, __up) \
for(j=k=0,i=__init;__cond;__up){\
    ans[i]+=k;\
    j+=boxes[i];\
    k+=j;\
}
        FORWARD(0, i < N, ++i);
        FORWARD(N - 1, i >= 0, --i);
        return ans;
    }
};

MAIN() {
    PREREQUISITES(minOperations);
    std::vector<int> ans = {11, 8, 5, 4, 3, 4};
    TEST(ans, "001011");
    ans = {1, 1, 3};
    TEST(ans, "110");
}
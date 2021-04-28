#include "solver_ex.h"

class Solution {
public:
    vector<int> runningSum(vector<int> &nums) {
        vector<int> ans;
        ans.swap(nums);
        for (int i = 1, N = ans.size(); i < N; ++i) {
            ans[i] += ans[i - 1];
        }
        return ans;
    }
};

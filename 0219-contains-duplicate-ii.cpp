//
// Created by Steve on 1/9/2021.
//

#include "solver_ex.h"

class Solution {
public:
    bool containsNearbyDuplicate(vector<int> &nums, int k) {
        unordered_map<int, int *> valueMapIndex;
        for (auto &i:nums) {
            if (valueMapIndex.count(i)) { // already meet value
                auto &indexRef = valueMapIndex[i];
                if (&i - indexRef > k) { // far away, update value's index
                    indexRef = &i;
                } else { // gotcha
                    return true;
                }
            } else { // first meet
                valueMapIndex[i] = &i;
            }
        }
        return false;
    }

    bool v2(vector<int> &nums, int k) {
        unordered_map<int, int> m;
        const int N = nums.size();
        if (N < 2) {
            return false;
        }
        m[nums.front()] = 0;
        for (int i = 1; i < N; ++i) {
            if (m.count(nums[i]) && i - m[nums[i]] <= k) {
                return true;
            }
            m[nums[i]] = i;
        }
        return false;
    }
};

MAIN() {
    PREREQUISITES(v2);
    vector<int> nums;
    nums = {1, 2, 3, 1};
    TEST(true, nums, 3);
    nums = {1, 0, 1, 1};
    TEST(true, nums, 1);
    nums = {1, 2, 3, 1, 2, 3};
    TEST(false, nums, 2);
}
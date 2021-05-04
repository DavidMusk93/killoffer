//
// Created by Steve on 1/23/2021.
//

#include "solver_ex.h"

class Solution {
public:
    void moveZeroes(vector<int> &nums) {
        int i, j;
        for (i = 0; i < nums.size() && nums[i] != 0; ++i);
        for (j = i; j < nums.size();) {
            for (++j; j < nums.size() && nums[j] == 0; ++j);
            if (j == nums.size()) {
                break;
            }
            swap(nums[i], nums[j]);
            for (++i; nums[i] != 0; ++i);
        }
    }

    void v2(vector<int> &nums) {
        int c = 0;
        for (auto &i:nums) {
            if (i) {
                if (c) {
                    swap(i, *(&i - c));
                }
            } else {
                ++c;
            }
        }
    }
};

MAIN() {
    PREREQUISITES(v2);
    vector<int> nums = {0, 1, 0, 3, 12};
    INVOKE(nums);
    cout << nums << endl;
}
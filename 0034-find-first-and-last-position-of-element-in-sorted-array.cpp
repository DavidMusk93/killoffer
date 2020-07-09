//
// Created by Steve on 6/30/2020.
//

#include <vector>

using namespace std;

class Solution {
public:
    vector<int> searchRange(vector<int> &nums, int target) {
        vector<int> res;
        res.push_back(binarySearch(nums, target, MOST_LEFT));
        res.push_back(binarySearch(nums, target, MOST_RIGHT));
        return res;
    }

private:
    enum {
        MOST_LEFT = -1,
        MOST_RIGHT = 1,
    };

    int binarySearch(const vector<int> &nums, int target, int type) {
        if (nums.empty()) {
            return -1;
        }
        int s, m, e, found = 0;
        for (s = 0, e = (int) nums.size() - 1; s < e;) {
            if (nums[s] > target || nums[e] < target) {
                break;
            }
            m = (s + e) >> 1;
            if (nums[m] == target) {
                found = 1;
                (type == MOST_LEFT ? e : s) = m + type;
            } else if (nums[m] > target) {
                e = m - 1;
            } else {
                s = m + 1;
            }
        }
        if (s == e && nums[s] == target) {
            return s;
        }
        return found ? (type == MOST_LEFT ? e : s) - type : -1;
    }
};

#include "macro.h"

MAIN() {
    vector<int> nums = {/*5,7,7,8,8,8*/2, 2};
    int target = 2;
    auto res = Solution().searchRange(nums, target);
    LOG("[%d,%d]", res[0], res[1]);
    return 0;
}
//
// Created by Steve on 6/27/2020.
//

#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

#define RETURN_TYPE vector<vector<int>>

class Solution {
public:
    vector<vector<int>> fourSum(vector<int> &nums, int target) {
        RETURN_TYPE out;
        int len;
        if ((len = nums.size()) < 4) {
            return out;
        }
        std::sort(nums.begin(), nums.end());
        int *in = nums.data();
        for (int i = 0, n = len - 3; i < n; ++i) {
            if (i > 0 && in[i] == in[i - 1]) {
                continue;
            }
            auto res = threeSum(in + i + 1, len - i - 1, target - in[i]);
            for (auto &v:res) {
                v.emplace_back(in[i]);
                out.emplace_back(std::move(v));
            }
        }
        for (auto &v:out) {
            std::reverse(v.begin(), v.end());
        }
        return out;
    }

private:
    static RETURN_TYPE threeSum(int *in, int len, int target) {
        RETURN_TYPE out;
        if (len < 3) {
            return out;
        }
        for (int i = 0, n = len - 2; i < n; ++i) {
            if (i > 0 && in[i] == in[i - 1]) {
                continue;
            }
            auto res = twoSum(in + i + 1, len - i - 1, target - in[i]);
            for (auto &v:res) {
                v.emplace_back(in[i]);
                out.emplace_back(std::move(v));
            }
        }
        return out;
    }

    static RETURN_TYPE twoSum(int *in/* sorted array */, int len, int target) {
        RETURN_TYPE out;
        if (len < 2) {
            return out;
        }
        int *p1, *p2, n1, n2, sum;
        for (p1 = in, p2 = in + len - 1; p1 != p2;) {
            n1 = *p1;
            n2 = *p2;
            sum = n1 + n2;
            if (sum < target) {
                ++p1;
            } else if (sum == target) {
                out.emplace_back(vector<int>{n2, n1});
                while (p1 != p2 && *++p1 == n1);
                while (p1 != p2 && *--p2 == n2);
            } else {
                --p2;
            }
        }
        return out;
    }
};

#include "macro.h"

#define FMT "%d,%d,%d,%d"
#define FOUR_ITEM(x) (x)[0],(x)[1],(x)[2],(x)[3]

MAIN() {
    std::vector<int> nums{-3, -2, -1, 0, 0, 1, 2, 3};
    int target = 0;
    auto res = Solution().fourSum(nums, target);
    for (auto &v:res) {
        LOG(FMT, FOUR_ITEM(v));
    }
    return 0;
}
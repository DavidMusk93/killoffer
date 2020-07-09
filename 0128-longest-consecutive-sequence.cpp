//
// Created by Steve on 7/6/2020.
//

#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int longestConsecutive(vector<int> &nums) {
        if (nums.empty()) {
            return 0;
        }
        unordered_map<int, int> um;
        int max = 1, l, r, n;
        for (auto i:nums) {
            if (!um.count(i)) {
                l = um.count(i - 1) ? um[i - 1] : 0; //l=um[i-1] do insert
                r = um.count(i + 1) ? um[i + 1] : 0;
                n = 1 + l + r;
                um[i] = n;
                if (l) {
                    um[i - l] = n;
                }
                if (r) {
                    um[i + r] = n;
                }
                if (max < n) {
                    max = n;
                }
            }
        }
        return max;
    }
};

#include "macro.h"

MAIN() {
    vector<int> data{100, 4, 200, 1, 3, 2};
    LOG("%d", Solution().longestConsecutive(data));
}
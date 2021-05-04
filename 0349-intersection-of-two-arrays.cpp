//
// Created by Steve on 1/23/2021.
//

#include "solver_ex.h"

class Solution {
public:
    vector<int> intersection(vector<int> &nums1, vector<int> &nums2) {
        vector<int> ans;
        unordered_set<int> unique;
        if (nums1.size() > nums2.size()) {
            nums1.swap(nums2);
        }
        for (auto i:nums1) {
            unique.insert(i);
        }
        for (auto i:nums2) {
            if (unique.count(i)) {
                ans.push_back(i);
                unique.erase(i);
            }
        }
        return ans;
    }
};
//
// Created by Steve on 2/7/2021.
//

#include "solver_ex.h"

class Solution {
public:
    vector<int> smallerNumbersThanCurrent(vector<int> &nums) {
        int i, j;
        int N = nums.size();
        vector<int> a(N, 0);
        for (i = 0; i < N; ++i) {
            for (j = i + 1; j < N; ++j) {
                if (nums[i] > nums[j]) {
                    ++a[i];
                } else if (nums[i] < nums[j]) {
                    ++a[j];
                }
            }
        }
        return a;
    }

    vector<int> v2(vector<int> &nums) {
#undef FORWARD_FOR
#define FORWARD_FOR(_i, _s, _e) for(_i=_s;_i<_e;++_i)
        int i, j;
        int N = nums.size();
        vector<int> a(N, 0);
        FORWARD_FOR(i, 0, N) {
            FORWARD_FOR(j, i + 1, N) {
                unsigned u = nums[i] - nums[j];
                if (u) {
                    ++a[(u >> 31) ? j : i];
                }
            }
        }
        return a;
    }

    vector<int> v3(vector<int> &nums) {
        vector<int> cache(101,-1); // follow the constrain
        priority_queue<int, deque<int>, greater<>> mh(nums.begin(), nums.end());
        int c = 0;
        while (!mh.empty()) {
            auto i = mh.top();
            mh.pop();
            if (cache[i]==-1) {
                cache[i] = c;
            }
            ++c;
        }
        vector<int> a(nums.size());
        for (auto &i:a) {
            i = cache[nums[&i - &a[0]]];
        }
        return a;
    }
    vector<int> v4(vector<int>&nums){
#define TN 104
        static short p[TN],q[TN];
        for(int i=0;i<TN;i+=4){
            *reinterpret_cast<size_t*>(p+i)=0; // fast assign
        }
        for(auto i:nums){
            ++p[i];
        }
        short c=0;
        for(int i=0;i<TN;++i){
            if(p[i]){
                q[i]=c;
                c+=p[i];
            }
        }
        vector<int> a;
        a.reserve(TN);
        for(auto i:nums){
            a.push_back(q[i]);
        }
        return a;
    }
};

MAIN() {
    PREREQUISITES(v4);
    vector<int> nums, ans;
    nums = {8, 1, 2, 2, 3};
    ans = {4, 0, 1, 1, 3};
    TEST(ans, nums);
    nums = {6, 5, 4, 8};
    ans = {2, 1, 0, 3};
    TEST(ans, nums);
    nums = {5, 0, 10, 0, 10, 6};
    ans = {2, 0, 4, 0, 4, 3};
    TEST(ans, nums);
}

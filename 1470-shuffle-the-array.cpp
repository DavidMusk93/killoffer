//
// Created by Steve on 1/7/2021.
//

#include "solver_ex.h"

class Solution {
public:
    int *m{}, i{}, j{}; // Tail recursion optimization?

    void __shuffle(int *p, int *q, int n) {
        if (n == 1) {

        } else if (n == 2) {
            std::swap(p[1], q[-2]);
        } else {
            m = q - n;
            // Phrase 1
            for (i = 1; i < n; i += 2) {
                std::swap(p[i], *m++);
            }
            // Phrase 2
            m = q - n;
            for (j = 2, i = j; j < n;) {
                if (i < n) {
                    std::swap(p[i], *m++);
                    i += 2;
                } else {
                    j += 2;
                    i = j;
                    m = q - n;
                }
            }
            if (n & 1) { // odd
                __shuffle(m - 1, q, n / 2 + 1);
            } else { // even
                __shuffle(m, q, n / 2);
            }
        }
    }

    vector<int> shuffle(vector<int> &nums, int n) {
        if (n < 2) {

        } else {
            __shuffle(nums.data(), nums.data() + nums.size(), n);
        }
        return nums;
    }
};

MAIN() {
    PREREQUISITES(shuffle);
    std::vector<int> data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    std::cout << INVOKE(data, data.size() / 2) << std::endl;
    data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
    std::cout << INVOKE(data, data.size() / 2) << std::endl;
}
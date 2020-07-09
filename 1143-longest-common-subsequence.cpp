//
// Created by Steve on 7/4/2020.
//

#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        int i, j, n1 = text1.size(), n2 = text2.size();
        vector<vector<int>> dp(n1, vector<int>(n2, 1));
        auto &l1 = dp[0];
        for (i = 0; i < n2; ++i) { //first line
            if (text1[0] == text2[i]) {
                break;
            }
            l1[i] = 0;
        }
        for (i = 0; i < n1; ++i) { //each line
            auto &v = dp[i]; //not work for l1=dp[i]
            if (text1[i] == text2[0]) {
                break;
            }
            v[0] = 0;
        }
        for (i = 1; i < n1; ++i) {
            for (j = 1; j < n2; ++j) {
                if (text1[i] == text2[j]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                } else {
                    dp[i][j] = ::max(dp[i][j - 1]/*left*/, dp[i - 1][j]/*top*/);
                }
            }
        }
        return dp[n1 - 1][n2 - 1];
    }
};

#include "macro.h"

MAIN() {
    LOG("%d", Solution().longestCommonSubsequence("abc", "def"));
}
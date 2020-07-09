//
// Created by Steve on 7/5/2020.
//

#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    string shortestCommonSupersequence(string str1, string str2) {
#define MIN(x, y) ((x)<(y)?(x):(y))
        int i, j, n1, n2, n;
        string res;
        n1 = str1.size(), n2 = str2.size();
        vector<vector<int>> dp(n1 + 1, vector<int>(n2 + 1));
        for (i = 0; i < n2 + 1; ++i) {
            dp[0][i] = i;
        }
        for (i = 1; i < n1 + 1; ++i) {
            dp[i][0] = i;
            for (j = 1; j < n2 + 1; ++j) {
                if (str1[i - 1] == str2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                } else {
                    dp[i][j] = MIN(dp[i][j - 1], dp[i - 1][j]) + 1;
                }
            }
        }
        n = dp[n1][n2];
        res.resize(n);
        while (n--) {
            if (!n1) {
                res[n] = str2[--n2];
            } else if (!n2) {
                res[n] = str1[--n1];
            } else if (str1[n1 - 1] == str2[n2 - 1]) {
                res[n] = str1[--n1];
                --n2;
            } else if (dp[n1][n2] == dp[n1 - 1][n2] + 1) {
                res[n] = str1[--n1];
            } else {
                res[n] = str2[--n2];
            }
        }
        return res;
    }
};
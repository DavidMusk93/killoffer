#include "solver_ex.h"

class Solution {
public:
    vector<int> maxDepthAfterSplit(const string &seq) {
        const int N = seq.size();
        vector<int> a(N, 0);
        int c{};
        for (int i = 0; i < N; ++i) {
            if (seq[i] == '(') {
                ++c;
                a[i] = c & 1;
            } else {
                a[i] = c & 1;
                --c;
            }
        }
        return a;
    }
};

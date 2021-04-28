#include "solver_ex.h"

class Solution {
public:
    int minPartitions(const string &n) {
        char a{};
        for (auto c:n) {
            if (a < c) {
                a = c;
            }
            if (a == '9') {
                return 9;
            }
        }
        return a - '0';
    }
};

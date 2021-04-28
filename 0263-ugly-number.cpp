#include "solver_ex.h"

class Solution {
public:
    bool isUgly(int n) {
        if (n < 1) {
            return false;
        } else if (n < 7) {
            return true;
        }
        while ((n & 1) == 0) {
            n >>= 1;
        }
        while ((n % 3) == 0) {
            n /= 3;
        }
        while ((n % 5) == 0) {
            n /= 5;
        }
        return n == 1;
    }
};

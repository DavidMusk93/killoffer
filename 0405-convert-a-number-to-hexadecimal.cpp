//
// Created by Steve on 1/31/2021.
//

#include "solver_ex.h"

struct field {
    unsigned char a: 4;
    unsigned char b: 4;
    unsigned char c: 4;
    unsigned char d: 4;
    unsigned char e: 4;
    unsigned char f: 4;
    unsigned char g: 4;
    unsigned char h: 4;
};

static const char HEX[] = "0123456789abcdef";

class Solution {
public:
    string toHex(int num) {
        static char ans[9];
        if (num == 0) {
            return "0";
        } else if (num > 0) {
            unsigned clz = __builtin_clz(num);
            auto p = ans + (clz >> 2);
            for (int i = 0, n = (32 - clz + 3) >> 2; i < n; ++i) {
                p[n - 1 - i] = HEX[(num >> (i << 2)) & 0xf];
            }
            return p;
        } else {
            auto p = (field *) &num;
            ans[7] = HEX[p->a];
            ans[6] = HEX[p->b];
            ans[5] = HEX[p->c];
            ans[4] = HEX[p->d];
            ans[3] = HEX[p->e];
            ans[2] = HEX[p->f];
            ans[1] = HEX[p->g];
            ans[0] = HEX[p->h];
            return ans;
        }
    }

    string v2(int num) {
        static char ans[9];
        if (num == 0) {
            return "0";
        }
        unsigned clz = __builtin_clz(num);
        auto p = ans + (clz >> 2);
        for (int i = 0, n = (32 - clz + 3) >> 2; i < n; ++i) {
            p[n - 1 - i] = HEX[(num >> (i << 2)) & 0xf];
        }
        return p;
    }

    string v3(int num) {
        static char ans[9];
        static const char *TABLE = "0123456789abcdef";
        if (!num) {
            return "0";
        }
        char *p = ans + 7;
        unsigned u = num;
        for (;;) {
            *p = TABLE[u & 0xf];
            u >>= 4;
            if (!u) {
                break;
            }
            --p;
        }
        return p;
    }
};

MAIN() {
    PREREQUISITES(v3);
    TEST("1a", 26);
    TEST("ffffffff", -1);
    TEST("3039", 12345);
    TEST("ffffcfc7", -12345);
    TEST("8", 8);
}

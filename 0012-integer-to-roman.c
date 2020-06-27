//
// Created by Steve on 6/25/2020.
//

struct roman_word_t {
    const char *s;
    int v;
    int len;
};
#define WORD struct roman_word_t

char *intToRoman(int num) {
#define BCOPY(x, y, n) do{for(int __i=0;__i<n;++__i){*(x)++=(y)[__i];}}while(0)
    static char data[64];
    char *p = data;
    static const WORD words[] = {
            {.s="M", .v=1000, .len=1},
            {.s="CM", .v=900, .len=2},
            {.s="D", .v=500, .len=1},
            {.s="CD", .v=400, .len=2},
            {.s="C", .v=100, .len=1},
            {.s="XC", .v=90, .len=2},
            {.s="L", .v=50, .len=1},
            {.s="XL", .v=40, .len=2},
            {.s="X", .v=10, .len=1},
            {.s="IX", .v=9, .len=2},
            {.s="V", .v=5, .len=1},
            {.s="IV", .v=4, .len=2},
            {.s="I", .v=1, .len=1},
    };
    int total = sizeof(words) / sizeof(WORD);
    int i, j, count;
    for (i = 0; i < total; ++i) {
        if ((count = num / words[i].v)) {
            for (j = 0; j < count; ++j) {
                BCOPY(p, words[i].s, words[i].len);
            }
            num -= count * words[i].v;
            if (!num) {
                break;
            }
        }
    }
    *p = 0;
    return data;
}

#include "macro.h"

MAIN() {
    LOG("%s", intToRoman(4));
    return 0;
}
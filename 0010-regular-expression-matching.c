//
// Created by Steve on 6/25/2020.
//

#include <stdbool.h>

#define PERIOD '.'
#define ASTERISK '*'
#define NORMAL(x) (x[1]!=ASTERISK)

bool isMatch(char *s, char *p) {
    if (!*s) {
        if (!*p) {
            return true;
        } else if (!NORMAL(p)) {
            return isMatch(s, p + 2);
        }
        return false;
    } else if (!*p) {
        return false;
    }
    for (; *s && *p && NORMAL(p) && (*s == *p || *p == PERIOD); ++s, ++p);
    if (!*s || !*p) {
        return isMatch(s, p);
    }
    if (NORMAL(p) && *s != *p) {
        return false;
    }
    if (*p != PERIOD && *s != *p) {
        return isMatch(s, p + 2);
    }
    return isMatch(s + 1, p) || isMatch(s, p + 2);
}

#include "macro.h"

MAIN() {
    char s[] = "a";
    char p[] = ".*..a*";
    LOG("%d", isMatch(s, p));
    return 0;
}
//
// Created by Steve on 6/25/2020.
//

#include <ctype.h>

#define MINUS '-'
#define PLUS '+'
#define ZERO '0'
#define INT_MIN 0x80000000
#define INT_MAX 0x7fffffff
#define WHERE_FALSE while(0)

int preprocessing(char **sp) {
    char *p;
    unsigned char c;
    for (p = *sp; (c = *p) && isspace(c); ++p);
    *sp = p;
    if (isdigit(c)) {
        return 1;
    } else if (c == MINUS) {
        return 2;
    } else if (c == PLUS) {
        return 3;
    }
    return 0;
}

int myAtoi(char *str) {
    do {
        char *p = str;
        unsigned int MAX = 0x80000000, b = MAX / 10;
        unsigned int i = 0;
        unsigned char c;
        int neg = 0;
        int ret = preprocessing(&p);
        if (ret == 0) {
            break;
        } else if (ret != 1) {
            if (ret == 2) {
                neg = 1;
            }
            ++p;
        }
        if (!isdigit(*p)) {
            break;
        }
        for (; isdigit((c = *p)); ++p) {
            if (i > b) {
                return neg ? INT_MIN : INT_MAX;
            }
            i = i * 10 + (c - ZERO);
        }
        if (i & MAX) {
            if (i & ~MAX) {
                return neg ? INT_MIN : INT_MAX;
            }
            if (!neg) {
                return INT_MAX;
            }
        }
        return (int) (neg ? -i : i);
    } WHERE_FALSE;
    return 0;
}

#include "macro.h"

MAIN() {
    char s[] = " -1234";
    LOG("'%s' -> '%d'", s, myAtoi(s));
    return 0;
}
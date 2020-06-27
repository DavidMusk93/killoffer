//
// Created by Steve on 6/25/2020.
//

#define ROMAN_I 1
#define ROMAN_V 5
#define ROMAN_X 10
#define ROMAN_L 50
#define ROMAN_C 100
#define ROMAN_D 500
#define ROMAN_M 1000

int parse_roman(char **sp) {
    if (!**sp) {
        return 0;
    }
    char *p = *sp, c;
    int v = 0;
    switch (*p++) {
        case 'I': {
            c = *p;
            if (c == 'V' || c == 'X') {
                ++p;
                v = c == 'V' ? 4 : 9;
            } else {
                v = 1;
            }
            break;
        }
        case 'V': {
            v = 5;
            break;
        }
        case 'X': {
            c = *p;
            if (c == 'L' || c == 'C') {
                ++p;
                v = c == 'L' ? 40 : 90;
            } else {
                v = 10;
            }
            break;
        }
        case 'L': {
            v = 50;
            break;
        }
        case 'C': {
            c = *p;
            if (c == 'D' || c == 'M') {
                ++p;
                v = c == 'D' ? 400 : 900;
            } else {
                v = 100;
            }
            break;
        }
        case 'D': {
            v = 500;
            break;
        }
        case 'M': {
            v = 1000;
            break;
        }
        default: {
        }
    }
    *sp = p;
    return v;
}

int romanToInt(char *s) {
    char *p;
    int res = 0, i;
    while ((i = parse_roman(&s))) {
        res += i;
    }
    return res;
}

#include "macro.h"

MAIN() {
    char s[] = "LVIII";
    LOG("%d", romanToInt(s));
    return 0;
}
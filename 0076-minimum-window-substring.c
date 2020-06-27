//
// Created by Steve on 6/24/2020.
//

#include <string.h>
#include <stdio.h>

struct string_view_t {
    char *start;
    char *end;
};
#define VIEW struct string_view_t

int string_view_great(VIEW *self, VIEW *other) {
    return (self->end - self->start) > (other->end - other->start);
}

#define MAP_SIZE 0x80

char *minWindow(char *s, char *t) {
    static char EMPTY[] = "";
    int m1[MAP_SIZE] = {}, m2[MAP_SIZE] = {};
    struct string_view_t min = {}, sv;
    char *p;
    unsigned char c, d;
    int count, total;
    for (count = total = 0, p = t; (c = *p); ++p) {
        if (m1[c]++ == 0) {
            ++count;
        }
        ++total;
    }
    for (p = s; (c = *p); ++p) {
        if (m1[c]) {
            if (!min.start) {
                min.start = p;
            }
            if (++m2[c] == m1[c]) {
                --count;
            }
            min.end = p + 1;
            if (!count) {
                break;
            }
        }
    }
    if (count) {
        return EMPTY;
    }
    if (total == min.end - min.start) {
        goto end;
    }
    sv = min;
    do {
        c = *sv.start;
        for (p = sv.start + 1;; ++p) {
            if (m2[(d = *p)]) {
                sv.start = p;
                break;
            }
        }
        if (m2[c]-- > m1[c]) {
            if (string_view_great(&min, &sv)) {
                min = sv;
            }
            continue;
        }
        for (p = sv.end; (d = *p); ++p) {
            if (m1[d]) {
                ++m2[d];
                if (d == c) {
                    break;
                }
            }
        }
        if (!d) {
            break;
        }
        sv.end = ++p;
        if (string_view_great(&min, &sv)) {
            min = sv;
        }
    } while (1);
    end:
    *min.end = 0;
    return min.start;
}

#define BLOCK_SIZE (sizeof(int)*8)
#define ARRAY_SIZE (MAP_SIZE/BLOCK_SIZE)
#define CHECK_BIT(x, n) (((x)[(n)/BLOCK_SIZE])&(1<<((n)%BLOCK_SIZE)))
#define SET_BIT(x, n) ((x)[(n)/BLOCK_SIZE]|=1<<((n)%BLOCK_SIZE))
#define CLEAR_BIT(x, n) ((x)[(n)/BLOCK_SIZE]&=~(1<<((n)%BLOCK_SIZE)))
#define INDEX(x) (unsigned char)(x)

char *minWindow_unique(char *s, char *t) {
    static char out[2048];
    *out = 0;
    unsigned int m1[ARRAY_SIZE] = {}, m2[ARRAY_SIZE], *mp;
    struct string_view_t min = {}, sv;
    int tmp, total;
    char *p, *q, *second, c;
    for (mp = m1, total = 0, p = t; *p; ++p) {
        if (!CHECK_BIT(mp, INDEX(*p))) { /* mark once */
            ++total;
            SET_BIT(mp, INDEX(*p));
        }
    }
    mp = m2;
    memcpy(mp, m1, sizeof m1);
    for (tmp = -1, p = s; *p; ++p) {
        if (CHECK_BIT(mp, INDEX(*p))) { /* find frist char */
            CLEAR_BIT(mp, INDEX(*p));
            min.start = p;
            tmp = total - 1;
            break;
        }
    }
    if (tmp == -1) { /* S does not contain all the characters in T */
        return out;
    } else if (tmp == 0) { /* T only contain one char */
        sprintf(out, "%c", *min.start);
        return out;
    }
    for (++p, second = 0; *p && tmp; ++p) {
        if (CHECK_BIT(mp, INDEX(*p))) {
            if (!second) { /* mark second char */
                second = p;
            }
            CLEAR_BIT(mp, INDEX(*p));
            --tmp;
        }
    }
    if (tmp > 0) {
        return out;
    }
    min.end = p;
    mp = m1;
    sv = min;
    do {
        p = sv.end;
        c = *sv.start;
        CLEAR_BIT(mp, c);
        sv.start = second;
        for (q = sv.start + 1; !(CHECK_BIT(mp, *q) && *q != c); ++q);
        if (!*q) {
            break;
        }
        second = q;
        for (; *p && *p != c; ++p); /* find next first-char from window end */
        if (!*p) {
            char c2 = *sv.start;
            int found = 0;
            second = 0;
            for (p = sv.start + 1; p < sv.end - 1; ++p) {
                if (!second && CHECK_BIT(mp, *p) && *p != c2) {
                    second = p;
                }
                if (*p == c) {
                    if (!second) {
                        second = p;
                    }
                    found = 1;
                    break;
                }
            }
            if (!found) {
                break;
            }
        } else {
            sv.end = p + 1;
        }
        if (sv.end - sv.start < min.end - min.start) {
            min = sv;
        }
        SET_BIT(mp, c);
    } while (*p);
    sprintf(out, "%.*s", (int) (min.end - min.start), min.start);
    return out;
}

#include "macro.h"

MAIN() {
    char S[] = "ADOBECODEBANC";
    char T[] = "ABC";
    LOG("%s", minWindow(S, T));
    return 0;
}
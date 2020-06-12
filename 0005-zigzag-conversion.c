//
// Created by Steve on 6/12/2020.
//

#include <stddef.h>
#include <string.h>
#include <stdlib.h>

int zigzag_loop(const char *in, size_t len, char *row[], size_t off[], const size_t k, const size_t n) {
    size_t i, j;
    for (i = 0; i < n && len > 0; ++i, --len) {
        j = i < k ? i : (n - i);
        row[j][off[j]++] = *in++;
    }
    return i;
}

char *zigzag_concat(const char *row[], size_t off[], const size_t k, char out[]) {
    for (size_t i = 0, n = 0; i < k; ++i) {
        memcpy(&out[n], row[i], off[i]);
        n += off[i];
    }
    return out;
}

const char *zigzag_convert(const char *in, size_t len, size_t k, char *out) {
    size_t n = (k << 1) - 2, p = (len / k + 1) << 1, q;
    char **row = malloc(k * sizeof(char *));
    char *data = malloc(k * p);
    size_t *off = malloc(k * sizeof(size_t));
    for (size_t i = 0; i < k; ++i) {
        row[i] = &data[i * p];
        off[i] = 0;
    }
    while ((q = zigzag_loop(in, len, row, off, k, n)) == n) {
        in += q;
        len -= q;
    }
    zigzag_concat((const char **) row, off, k, out);
    free(row), free(data), free(off);
    return out;
}

//char *convert(char *in, int k) {
//    if (!in) {
//        return in;
//    }
//    size_t len = strlen(in);
//    if (len < 2 || k == 1) {
//        return in;
//    }
//    static char out[4096];
//    out[len] = 0;
//    return (char *) zigzag_convert((const char *) in, len, k, out);
//}

//#define TEST_ZIGZAG 1
#if TEST_ZIGZAG

#include "macro.h"

MAIN_EX(argc, argv) {
    const char in[] = "PAYPALISHIRING";
    const size_t len = sizeof(in) - 1;
    char out[len + 1];
    out[len] = 0;
    size_t k = 3;
    if (argc > 1) {
        k = strtol(argv[1], 0, 10);
        k = k < 2 ? 2 : k;
    }
    zigzag_convert(in, len, k, out);
    puts(out);
    return 0;
}

#endif
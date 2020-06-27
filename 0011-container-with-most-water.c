//
// Created by Steve on 6/27/2020.
//

int maxArea(int *height, int heightSize) {
    int a1, a2, n1, n2, max, *p1, *p2;
    a1 = max = 0;
    p1 = height, p2 = height + heightSize - 1;
    do {
        n1 = *p1;
        n2 = *p2;
        max = n1 > n2 ? n1 : n2;
        a2 = (n1 + n2 - max) * --heightSize;
        if (a1 < a2) {
            a1 = a2;
        }
        if (max == n1) {
            --p2;
        } else {
            ++p1;
        }
    } while (p1 != p2);
    return a1;
}

#include "macro.h"

MAIN() {
    int data[] = {1, 8, 6, 2, 5, 4, 8, 3, 7};
    LOG("%d", maxArea(data, sizeof(data) / sizeof(int)));
    return 0;
}
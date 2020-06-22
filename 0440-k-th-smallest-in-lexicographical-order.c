#include "macro.h"

static long get_virtual_children(long parent, long n) {
    long sibling = parent + 1;
    long count = 0;
    while (parent * 10 <= n) {
        parent *= 10;
        sibling *= 10;
        count += (n <= sibling ? n + 1 : sibling) - parent;
    }
    return count;
}

int findKthNumber(int n, int k) {
    long parent = 1;
    for (long traced = 1, count; traced < k;) {
        count = get_virtual_children(parent, n);
        if (traced++ + count >= k) {
            parent *= 10;
        } else {
            ++parent;
            traced += count;
        }
    }
    return (int) parent;
}

//MAIN() {
//    LOG("%d", findKthNumber(13, 2));
//    return 0;
//}
#include <stdio.h>
#include <string.h>

#include <vector>

#include "Sort.h"

void MergeSort(void *a, size_t n, size_t c, compare_t cmp) {
    // Assume type size is less than 256 bytes
    static __thread char t[256];
    char *a1, *a2, *tp;
    size_t n1, n2;
    n1 = n / 2;
    n2 = n - n1;
    a1 = (char *) a;
    a2 = a1 + n1 * c;
    if (n1 > 1)
        MergeSort(a1, n1, c, cmp);
    if (n2 > 1)
        MergeSort(a2, n2, c, cmp);
    while (n2--) {
        for (; cmp(a1, a2) < 0; a1 += c);
        if (a1 == a2)
            return;
        tp = a2;
        memcpy(t, tp, c);
        for (; a1 < a2; a2 -= c)
            memcpy(a2, a2 - c, c);
        memcpy(a1, t, c);
        a1 += c;
        a2 = tp + c;
    }
}

static int greater(const void *a, const void *b) {
    return *(int *) a - *(int *) b;
}

static int less(const void *a, const void *b) {
    return -*(int *) a + *(int *) b;
}

static void MergeSort(int *a, int n) {
    int *a2, n2, t, *tp;
    n2 = n / 2;
    n -= n2;
    a2 = a + n;
    // Sort left side
    if (n > 1)
        MergeSort(a, n);
    // Sort right side
    if (n2 > 1)
        MergeSort(a2, n2);
    while (n2--) {
        for (; *a < *a2; ++a);
        if (a == a2)
            return;
        tp = a2;
        t = *tp;
        // Move forward one step for [a,a2)
        for (; a < a2; --a2)
            a2[0] = a2[-1];
        *a++ = t;
        a2 = ++tp;
    }
}

#if 0
int main()
{
  int i,n;
  std::vector<int> v={3,10,4,8,10,2,1,16,7};
  n=v.size();
  // MergeSort(v.data(),n);
  MergeSort(v.data(),n,sizeof(int),less);
  for (i=0; i<n; ++i) {
    if (!i)
      printf("%d",v[i]);
    else
      printf(" %d",v[i]);
  }
  putchar('\n');
  return 0;
}
#endif

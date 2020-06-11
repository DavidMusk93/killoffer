#include <stdio.h>
#include <stdlib.h>

#include <vector>
#include <algorithm>

static void dump_vector(std::vector<int> &v) {
    const char *fmt[] = {" %d", "%d"};
    int i, n;
    for (i = 0, n = v.size(); i < n; ++i)
        printf(fmt[!i], v[i]);
    putchar('\n');
}

bool solver(std::vector<int> &res, int *a, const int n, const int m, const int target) {
    static __thread int pop, i, sum, pre, diff;
    if (m == (int) res.size()) {
#ifdef DEBUG
        dump_vector(res);
#endif
        for (i = sum = 0; i < m; ++i)
            sum += res[i];
        diff = sum - target;
        if (diff < 0)
            return false;
        if (!diff)
            return true;
        if ((pre = sum - a[-1] + pop, diff - (target - pre) > 0)) {
            res.pop_back();
            res.push_back(pop);
        }
        return true;
    }
    if (!n)
        return false;
    res.push_back(a[0]);
    if (solver(res, a + 1, n - 1, m, target))
        return true;
    pop = res.back();
    res.pop_back();
    return solver(res, a + 1, n - 1, m, target);
}

int main() {
    /* Never let trivial things (preprocessing for this) bother you! */
    // int a1[] = {-3,9,8,10,65};
    // int a2[] = {5,6,8,13,55};
    // int i,n,target=0;
    // n=sizeof(a1)/sizeof(int);
    // std::vector<int> v(2*n);
    // std::vector<int> v2,res;
    // v2.reserve(2*n);
    // for (i=0; i<n; ++i)
    //   v[i]=a1[i];
    // for (i=0; i<n; ++i)
    //   v[i+n]=a2[i];
    // std::sort(v.begin(),v.end());
    // for (i=0,n=2*n-1; i<n; ++i) {
    //   if (v[i]==v[i+1])
    //     ++i;
    //   else
    //     v2.push_back(v[i]);
    // }
    // if (i==n)
    //   v2.push_back(v[i]);
    // const char *fmt[] = {" %d","%d"};
    // for (i=0,n=v2.size(); i<n; ++i) {
    //   printf(fmt[!i],v2[i]);
    //   target+=v2[i];
    // }
    // putchar('\n');
    // n/=2;

    /* Test set */
    std::vector<int> data = {-3, 5, 6, 9, 10, 13, 55, 65};
    std::vector<int> data2 = {1, 2, 3, 4, 5, 6, 7, 1000};
    std::vector<int> data3 = {-10, 2, 3, 4, 5, 6, 7, 10};

    std::vector<int> v2, res;
    v2 = std::move(data3);
    int i, n, target;
    for (i = target = 0, n = v2.size(); i < n; ++i)
        target += v2[i];
    res.reserve(n);
    solver(res,
           v2.data() + 1,
           n - 1,
           n / 2 - 1,
           target / 2 - v2[0]);

    /* Show result */
    puts("one array:");
    printf("%d\n", v2[0]);
    for (i = 0, n = res.size(); i < n; ++i)
        printf("%d\n", res[i]);
    return 0;
}

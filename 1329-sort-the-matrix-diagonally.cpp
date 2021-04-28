#include "solver_ex.h"

class Solution {
public:
    vector<vector<int>> diagonalSort(vector<vector<int>> &mat) {
        const int M = mat.size(), N = mat[0].size();
        if (M == 1 || N == 1) {
            return mat;
        }
        std::vector<int> a;
        std::vector<int *> b;
#define SORT(i, j) \
int __i=i,__j=j;\
do{\
    int&v=mat[__i++][__j++];\
    a.push_back(v);\
    b.push_back(&v);\
}while(__i<M&&__j<N);\
std::sort(a.begin(),a.end());\
for(auto&p:b){\
    *p=a[&p-&b[0]];\
}\
a.clear(),b.clear()
        for (int i = M - 2; i >= 0; --i) {
            SORT(i, 0);
        }
        for (int i = N - 1; --i;) {
            SORT(0, i);
        }
        return mat;
    }
};

#include "solver_ex.h"

class Solution {
public:
    TreeNode *v2(vector<int> &nums) {
        static int a[1001][1001];
        static TreeNode *v[1001];
        const int N = nums.size();
        int i, j, k;
        for (i = 0; i < N; ++i) {
            v[nums[i]] = new TreeNode(nums[i]);
            a[i][i] = i;
            for (j = i + 1; j < N; ++j) {
                k = a[i][j - 1];
                a[i][j] = nums[k] < nums[j] ? j : k;
            }
        }
        std::function<TreeNode *(int, int)> op;
        op = [&op, &nums](int s, int e) -> TreeNode * {
            if (s <= e) {
                auto m = a[s][e];
                auto *t = v[nums[m]];
                if (s < m) {
                    t->left = op(s, m - 1);
                }
                if (m < e) {
                    t->right = op(m + 1, e);
                }
                return t;
            }
            return nullptr;
        };
        return op(0, N - 1);
    }

    TreeNode *constructMaximumBinaryTree(vector<int> &nums) {
//        static struct {
//            int i, v;
//        } a[1001][1001];
        static int a[1001][1001];
        const int N = nums.size();
        int i, j, k;
        for (i = 0; i < N; ++i) {
            a[i][i] = i;
            for (j = i + 1; j < N; ++j) {
                k = a[i][j - 1];
                a[i][j] = nums[k] < nums[j] ? j : k;
            }
        }
//        std::function<TreeNode *(int, int)> op;
//        op = [&op, &nums](int s, int e/*[s,e]*/) -> TreeNode * {
//            if (s <= e) {
//                int i = a[s][e];
//                return new TreeNode(nums[i], op(s, i - 1), op(i + 1, e));
//            }
//            return nullptr;
//        };
//        return op(0, N - 1);
        std::vector<TreeNode *> v(N);
        struct entry {
            int s, m, e;
        };
        k = a[0][N - 1];
        v[k] = new TreeNode(nums[k]);
        std::queue<entry> q;
        q.push({0, k, N - 1});
        while (!q.empty()) {
            auto it = q.front();
            q.pop();
            if (it.s < it.m) {
                i = a[it.s][it.m - 1];
                v[it.m]->left = v[i] = new TreeNode(nums[i]);
                q.push({it.s, i, it.m - 1});
            }
            if (it.m < it.e) {
                i = a[it.m + 1][it.e];
                v[it.m]->right = v[i] = new TreeNode(nums[i]);
                q.push({it.m + 1, i, it.e});
            }
        }
        return v[k];
    }
};

//
// Created by Steve on 6/30/2020.
//

#include <string>
#include <vector>

using namespace std;

struct Block {
    int s;
    int e;

    void update(int &max) {
        int diff = e - s;
        if (max < diff) {
            max = diff;
        }
    }
};

class Solution {
public:
    int longestValidParentheses(string s) {
#define PL '('
        Block block{};
        vector<int> pl;
        vector<Block> pre;
        int i, n, max;
        for (i = max = 0, n = s.size(); i < n; ++i) {
            if (s[i] == PL) {
                pl.push_back(i);
            } else if (pl.empty()) {
                block = Block{};
            } else {
                int start = pl.back();
                pl.pop_back();
                if (start + 1 == block.s) { //(())
                    block = Block{start, i + 1};
                } else if (start == block.e) { //()()
                    block.e = i + 1;
                } else { //()(())
                    pre.push_back(block);
                    block = Block{start, i + 1};
                }
                update(pre, block, max);
            }
        }
        update(pre, block, max);
        return max;
    }

private:
    void update(vector<Block> &pre, Block &block, int &max) {
        if (!pre.empty()) {
            auto &last = pre.back();
            if (last.e == block.s) {
                last.e = block.e;
                block = last;
                pre.pop_back();
            }
        }
        block.update(max);
    }
};

#include "macro.h"

MAIN() {
    auto solver = Solution();
#define FMT "%s -> %d"
#define DATA(x) x,solver.longestValidParentheses(x)
#define TEST(x) LOG(FMT,DATA(x))
    TEST("()(())");
    TEST("(()");
    TEST(")()())");
    return 0;
}
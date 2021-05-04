//
// Created by Steve on 12/20/2020.
//

#include "solver_ex.h"

class Solution {
 public:
  vector<vector<int>> ans;
  int sum, TARGET, N;
  void op(vector<int> &candidates, vector<int> &seq, int i) {
    for (int j = i; j < N; ++j) {
      if (j != i && candidates[j - 1] == candidates[j]) {
        continue;
      }
      int k = candidates[j];
      seq.push_back(k);
      sum += k;
      sun::Defer c1([this, k] { sum -= k; });
      sun::Defer c2([&seq] { seq.pop_back(); });
      if (sum >= TARGET) {
        if (sum == TARGET) {
          ans.push_back(seq);
        }
        break;
      }
      op(candidates, seq, j + 1);
    }
  }

  vector<vector<int>> combinationSum2(vector<int> &candidates, int target) {
    vector<int> t;
    vector<vector<int>> res;
    for (auto i:candidates) {
      if (i <= target) {
        t.push_back(i);
      }
    }
    std::sort(t.begin(), t.end());
    sum = 0;
    TARGET = target;
    N = t.size();
    vector<int> seq;
    op(t, seq, 0);
    ans.swap(res);
    return res;
  }
};

MAIN() {
  PREREQUISITES(combinationSum2);
  vector<int> candidates = {2, 5, 2, 1, 2};
  std::cout << INVOKE(candidates, 5) << std::endl;
  candidates = {10, 1, 2, 7, 6, 1, 5};
  std::cout << INVOKE(candidates, 8) << std::endl;
}
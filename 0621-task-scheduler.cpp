//
// Created by Steve on 7/8/2020.
//

#include <vector>

using namespace std;

class Solution {
public:
    int leastInterval(vector<char> &tasks, int n) {
#define SIZE 26
        if (tasks.size() == 1 || n == 0) {
            return tasks.size();
        }
        int count[SIZE] = {}, m, i, k;
        for (auto c:tasks) { //wrod frequency statistics
            ++count[c - 'A'];
        }
        for (m = -1, i = k = 0; i < SIZE; ++i) { //find maximum
            if (m < count[i]) {
                m = count[i];
                k = 1;
            } else if (m == count[i]) {
                ++k;
            }
        }
        return max((m - 1) * (n + 1) + k, (int) tasks.size()); //same type
    }
};
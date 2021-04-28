class Solution {
public:
    int numIdenticalPairs(vector<int> &nums) {
        char a[101]{};
        int c{};
        for (auto i:nums) {
            ++a[i];
        }
        for (auto i:a) {
            if (i > 1) {
                c += i * (i - 1) / 2;
            }
        }
        return c;
    }
};

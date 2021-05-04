//
// Created by Steve on 1/23/2021.
//

#include "solver_ex.h"

class Solution {
public:
    class State {
    public:
        State() : u_(0) {}

        void initialize(int a, int b, int c) {
            u_ |= ((a == b) << 1) + (b == c);
        }

        explicit operator bool() const {
            return (u_ & 6) == 6;
        }

        State &operator<<(int i) {
            u_ <<= i;
            return *this;
        }

        void update(bool b) {
            u_ = (u_ << 1) + b;
        }

    private:
        unsigned char u_;
    };

    int removeDuplicates(vector<int> &nums) {
        int c = 0;
        State state;
        const int N = nums.size();
        if (N > 2) {
            state.initialize(nums[0], nums[1], nums[2]);
        }
//        nums.push_back(0); // avoid overflowing
        for (int i = 2; i < N; ++i) {
            if (i + 1 != N) {
                state.update(nums[i] == nums[i + 1]);
            } else {
                state << 1;
            }
            if (bool(state)) {
                ++c;
            } else {
                if (c) {
                    swap(nums[i], nums[i - c]);
                }
            }
        }
        return N - c;
    }
};

// [1,2,3,3]
// [1,1,1]

MAIN() {
    PREREQUISITES(removeDuplicates);
    vector<int> nums{1, 1, 1, 1, 2, 2, 2, 3, 4, 5, 5, 6};
    cout << INVOKE(nums) << ",";
    cout << nums << endl;
}
#include "solver_ex.h"

/*log first*/
class SubrectangleQueries {
public:
    class Op {
    public:
        Op(int r1, int c1, int r2, int c2, int v) : r1_(r1), c1_(c1), r2_(r2), c2_(c2), v_(v) {}

        int *has(int r, int c) {
            if (r1_ <= r && r <= r2_ && c1_ <= c && c <= c2_) {
                return &v_;
            }
            return nullptr;
        }

    private:
        int c1_, r1_, c2_, r2_, v_;
    };

    SubrectangleQueries(vector<vector<int>> &rectangle) : raw_(rectangle) {}

    void updateSubrectangle(int row1, int col1, int row2, int col2, int newValue) {
        wal_.push_front({row1, col1, row2, col2, newValue});
    }

    int getValue(int row, int col) {
        int *p;
        for (auto &op:wal_) {
            if ((p = op.has(row, col))) {
                return *p;
            }
        }
        return raw_[row][col];
    }

    std::list<Op> wal_;
    vector<vector<int>> &raw_;
};

/**
 * Your SubrectangleQueries object will be instantiated and called as such:
 * SubrectangleQueries* obj = new SubrectangleQueries(rectangle);
 * obj->updateSubrectangle(row1,col1,row2,col2,newValue);
 * int param_2 = obj->getValue(row,col);
 */

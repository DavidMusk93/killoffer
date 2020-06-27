//
// Created by Steve on 6/27/2020.
//

#include <string>
#include <vector>
#include <map>

using namespace std;

class Solution {
public:
    vector<string> letterCombinations(string digits) {
        const std::map<char, const char *> m = {
                {'2', "abc"},
                {'3', "def"},
                {'4', "ghi"},
                {'5', "jkl"},
                {'6', "mno"},
                {'7', "pqrs"},
                {'8', "tuv"},
                {'9', "wxyz"},
        };
        std::vector<std::string> out;
        if (digits.empty()) {
            return out;
        }
        std::vector<const char *> in;
        std::string data;
        char *p;
        for (auto i:digits) {
            in.push_back(m.at(i));
        }
        data.resize(digits.size() + 1);
        p = (char *) data.data();
        combine(out, in, 0, p);
        return out;
    }

private:
    void combine(std::vector<std::string> &out, const std::vector<const char *> &in, int off, char *p) {
        if (off == in.size()) {
            out.emplace_back(p);
            return;
        }
        char c;
        for (const char *s = in[off]; (c = *s); ++s) {
            p[off] = c;
            combine(out, in, off + 1, p);
        }
    }
};

#include "macro.h"

MAIN() {
    auto res = Solution().letterCombinations("23");
    for (const auto &i:res) {
        LOG("%s", i.c_str());
    }
    return 0;
}
//
// Created by Steve on 7/18/2020.
//

#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        if (s.size() < p.size()) {
            return {};
        }
        vector<int> res;
        vector<int> v1 = vector<int>(26, 0);
        vector<int> v2 = v1;
        for (auto &i:p) {
            ++v1[i - 'a'];
        }
        for (int i = 0; i < p.size(); ++i) {
            ++v2[s[i] - 'a'];
        }
        if (v1 == v2) {
            res.push_back(0);
        }
        for (int i = p.size(); i < s.size(); ++i) {
            --v2[s[i - p.size()] - 'a'];
            ++v2[s[i] - 'a'];
            if (v1 == v2) {
                res.push_back(i - p.size() + 1);
            }
        }
        return res;
    }
};
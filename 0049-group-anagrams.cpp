//
// Created by Steve on 7/18/2020.
//

#include <vector>
#include <unordered_map>

using namespace std;

struct MaskHash{
    size_t operator()(const vector<int>&v) const{
        size_t h=0;
        for(int i=0;i<26;++i){
            if(v[i]){
                h|=1<<i;
            }
        }
        return h;
    }
};

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<vector<int>,int,MaskHash> m; //Does order matter?map:unordered_map
        int count=0;
        vector<vector<string>> res;
        for(auto&s:strs){
            vector<int> mask(26,0);
            for(auto&i:s){
                mask[i-'a']++;
            }
            if(m.count(mask)){
                res[m[mask]].push_back(s);;
            }else{
                m[mask]=count++;
                res.emplace_back(vector<string>{s});
            }
        }
        return res;
    }
};
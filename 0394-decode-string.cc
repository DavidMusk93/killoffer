//
// Created by Steve on 6/20/2020.
//

#include <string>
#include <assert.h>
#include <ctype.h>

//#include "macro.h"

class Solution {
#define GROUP_BEGIN '['
#define GROUP_END   ']'
public:
    std::string decodeString(std::string s) {
        std::string data = "1[" + s + "]";
        const char *p = data.c_str();
        return decode(&p);
    }

private:
    std::string decode(const char **sp) {
        std::string res, group;
        const char *p = *sp;
        char *end;
        int k = (int) strtol(p, &end, 10);
//        assert(*end == GROUP_BEGIN);
        p = ++end;
        while (*p != GROUP_END) {
            if (isdigit(*p)) {
                group += decode(&p);
            } else {
                group += *p++;
            }
        }
        *sp = ++p;
        if (k == 1) {
            return group;
        }
        res.reserve(k * group.size());
        while (k--) {
            res += group;
        }
        return res;
    }
};

//#include <iostream>
//
//MAIN() {
//    char s[] = "3[a2[c]]";
//    const char *p = s;
//    std::cout << Solution().decode(&p) << std::endl;
//    return 0;
//}
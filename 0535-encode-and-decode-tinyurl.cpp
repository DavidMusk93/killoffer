#include "solver_ex.h"

#include <random>
#include <utility>

class Solution {
public:
    static constexpr const char base58[] = "123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz";
    static constexpr const char url_prefix[] = "http://tinyurl.com/";

    // Encodes a URL to a shortened URL.
    string encode(string longUrl) {
        string key;
        for (;;) {
            auto c6 = GetChar6();
            if (m_[c6].empty()) {
                key.swap(c6);
                break;
            }
        }
        m_[key] = std::move(longUrl);
        return url_prefix + key;
    }

    // Decodes a shortened URL to its original URL.
    string decode(const string &shortUrl) {
        return m_[shortUrl.c_str() + sizeof(url_prefix) - 1];
    }

protected:
    string GetChar6() {
        static std::random_device r;
        static std::default_random_engine engine{r()};
        static std::uniform_int_distribution<int> uniform(0, 57);
        std::string c6(6, 0);
        for (int i = 0; i < 6; ++i) {
            c6[i] = base58[uniform(engine)];
        }
        return c6;
    }

private:
    std::map<string, string> m_;
};

// Your Solution object will be instantiated and called as such:
// Solution solution;
// solution.decode(solution.encode(url));

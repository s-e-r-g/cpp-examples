#include <iostream>
#include <string>
#include <algorithm>
#include <bitset>
#include <unordered_map>

/*
  6 d a a 6 c c a a a 6 d
----------------------------
6 x x x x             x x  |
a     x         x   x x x  hash
c           x              |
d   x x x x x x x x x x    |
----------------------------
*/

int solution(const std::string &S)
{
    using Hash = std::bitset<128>;
    
    std::unordered_map<Hash, size_t> map;

    Hash hash;
    
    for (size_t i = 0; i < S.size(); ++i)
    {
        hash.flip(S[i]);
        map[hash] = i;
    }

    size_t maxLen = 0;
    hash.reset();
    for (size_t i = 0; i < S.size(); ++i)
    {
        const auto it = map.find(hash);
        if (it != map.end())
        {
            if (it->second > i)
            {
                maxLen = std::max(maxLen, it->second - i + 1);
            }
        }
        
        hash.flip(S[i]);
    }
    
    return maxLen;
}

void test(const std::string& s)
{
    std::cout << s << " : " << solution(s) << std::endl;
}

int main()
{
    test("6daa6ccaaa6d");
}

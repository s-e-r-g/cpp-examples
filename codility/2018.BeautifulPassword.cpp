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
    
    std::unordered_map<Hash, int> map;

    Hash hash;

    map.insert({hash, -1});
    
    int len = (int)S.size();
    int maxLen = 0;    
    for (int i = 0; i < len; ++i)
    {
        hash.flip(S[i]);
        const auto inserted = map.insert({hash, i});
        if (!inserted.second)
        {
            maxLen = std::max(maxLen, i - inserted.first->second);
        }
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

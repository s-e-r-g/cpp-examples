#include <string>
#include <algorithm>
#include <queue>

int solution(std::string& S, int K)
{
    if (K < 0)
    {
        return -1;
    }
    
    size_t k = (size_t)K;

    if (S.empty())
    {
        return k == 0 ? 0 : -1;
    }

    if (k == 0)
    {
        return std::count(S.begin(), S.end(), 'M');
    }
    
    if (k > S.size())
    {
        return -1;
    }
    
    if (k == S.size())
    {
        return std::count(S.begin(), S.end(), 'L');
    }
    
    // Check if there is a wider range of M, split it

    int changes = 0;

    char rangeLetter = '?';
    size_t rangeSize = 0;
    
    for (const auto c : S)
    {
        if (c != rangeLetter)
        {
            rangeLetter = c;
            rangeSize = 1;
        }
        else
        {
            if (rangeLetter == 'M' && rangeSize == k)
            {
                rangeLetter = 'L';
                rangeSize = 1;
                ++changes;
            }
            else
            {
                ++rangeSize;
            }
        }
    }

    if (changes > 0)
    {
        return changes;
    }
    
    // Shift window of size K, counting changes inside, 
    // calculate minimum, including possible border changes.
    size_t windowStart = 0;
    size_t windowEnd = 0;
    size_t maxWindowEnd = S.size() - 1;
    
    std::queue<int> queue;
    changes = 0;
    
    int minChanges = k + 2;
    
    for (; windowEnd <= maxWindowEnd; ++windowEnd)
    {
        if (queue.size() == k)
        {
            changes -= queue.front();
            queue.pop();            
        }

        int change = S[windowEnd] == 'L' ? 1 : 0;
        queue.push(change);
        changes += change;

        if (queue.size() == k)
        {
            int borderChanges = (windowStart > 0 && S[windowStart - 1] == 'M') ? 1 : 0;
            borderChanges += (windowEnd < maxWindowEnd && S[windowEnd + 1] == 'M') ? 1 : 0;

            minChanges = std::min(minChanges, changes + borderChanges);
            
            ++windowStart;
        }
    }


    return minChanges;
}

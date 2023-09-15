class Solution {
private:
    std::vector<int> cache = {0, 1};
    
public:
    int fib_(int n)
    {
        if (cache.size() >= n + 1)
        {
            return cache[n];
        }

        auto result = fib_(n - 1) + fib_(n - 2);
        cache.push_back(result);
        return result;
    }
    
    int fib(int n)
    {
        cache.reserve(n + 1);
        return fib_(n);
    }
};

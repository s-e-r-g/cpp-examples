int solution(vector<bool> &P) 
{
    size_t zeroCount = 0;
    size_t ones = 0;
    for (size_t i = 0; i < P.size(); ++i)
    {
        zeroCount = P[i] ? 0 : (zeroCount + 1);
        ones += i + 1 - zeroCount;
        if (ones > 1000000000)
        {
            return 1000000000;
        }
    }
    return ones;
}

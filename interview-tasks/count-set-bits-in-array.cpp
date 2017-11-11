#include <iostream>
#include <iomanip>
#include <ctime>
#include <chrono>
#include <vector>
 
 
size_t calc(const std::vector<std::uint64_t>& array)
{
    size_t count = 0;
    for (auto c : array)
    {
        for (std::uint64_t mask = (1ul << 63); mask != 0 ; mask >>= 1) 
        {
            count += c & mask ? 1 : 0;
        }
    }
    
    return count;
}

size_t calc1(const std::vector<std::uint64_t>& array)
{
    size_t count = 0;
    for (auto c : array)
    {
        while (c)
        {
            count += c & 1;
            c >>= 1;
        }
    }
    
    return count;
}


static const std::uint8_t table[256] = 
{
    0,1,1,2,1,2,2,3,1,2,2,3,2,3,3,4,
    1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,
    1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,
    2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
    1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,
    2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
    2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
    3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,
    1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,
    2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
    2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
    3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,
    2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
    3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,
    3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,
    4,5,5,6,5,6,6,7,5,6,6,7,6,7,7,8
};

size_t calc2(const std::vector<std::uint64_t>& array)
{
    size_t count = 0;
    for (auto c : array)
    {
        count += table[c & 0xff];
        c >>= 8;
        count += table[c & 0xff];
        c >>= 8;
        count += table[c & 0xff];
        c >>= 8;
        count += table[c & 0xff];
        c >>= 8;
        count += table[c & 0xff];
        c >>= 8;
        count += table[c & 0xff];
        c >>= 8;
        count += table[c & 0xff];
        c >>= 8;
        count += table[c & 0xff];
    }
    
    return count;
}

size_t calc3(const std::vector<std::uint64_t>& array)
{
    size_t count = 0;
    for (const auto c : array)
    {
        count += table[c & 0xff];
        count += table[c >> 8 & 0xff];
        count += table[c >> 16 & 0xff];
        count += table[c >> 24 & 0xff];
        count += table[c >> 32 & 0xff];
        count += table[c >> 40 & 0xff];
        count += table[c >> 48 & 0xff];
        count += table[c >> 56 & 0xff];
    }
    
    return count;
}

size_t calc4(const std::vector<std::uint64_t>& array)
{
    size_t totalCount = 0;
    
    for (const auto c : array)
    {
        auto count = table[c & 0xff];
        count += table[c >> 8 & 0xff];
        count += table[c >> 16 & 0xff];
        count += table[c >> 24 & 0xff];
        count += table[c >> 32 & 0xff];
        count += table[c >> 40 & 0xff];
        count += table[c >> 48 & 0xff];
        count += table[c >> 56 & 0xff];
        totalCount += count;
    }
    
    return totalCount;
}

size_t calc5(const std::vector<std::uint64_t>& array)
{
    size_t totalCount = 0;

    constexpr std::uint64_t mask = (1ul << 56) | (1ul << 48) | (1ul << 40) | (1ul << 32) | (1ul << 24) | (1ul << 16) | (1ul << 8) | (1ul << 0);

    std::uint64_t multiCounter = 0;

    for (const auto c : array)
    {
        multiCounter+= (c & mask) + (c >> 1 & mask) + (c >> 2 & mask) + (c >> 3 & mask) + (c >> 4 & mask) + (c >> 5 & mask) + (c >> 6 & mask) + (c >> 7 & mask);
        
        if (multiCounter & 0b1000000010000000100000001000000010000000100000001000000010000000)
        {
            totalCount += (multiCounter & 0xff) + (multiCounter >> 8 & 0xff) + (multiCounter >> 16 & 0xff) + (multiCounter >> 24 & 0xff)
             + (multiCounter >> 32 & 0xff) + (multiCounter >> 40 & 0xff) + (multiCounter >> 48 & 0xff) + (multiCounter >> 56 & 0xff);
             
            multiCounter =  0;
        }
    }

    return totalCount;
}

int main()
{
    std::vector<std::uint64_t> a(1000000);
    for (size_t i = 0; i < a.size(); ++i) a[i] = 0b1010101010101010101010101010101010101010101010101010101010101010;
    
    auto start = std::chrono::steady_clock::now();
    size_t count = calc(a);   
    auto end = std::chrono::steady_clock::now();
    std::cout << "Direct Shift Execution took " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "us.\n";
    std::cout << "Count: " << count << "\n";
    
    start = std::chrono::steady_clock::now();
    count = calc1(a);   
    end = std::chrono::steady_clock::now();
    std::cout << "Direct Shift (Opt) Execution took " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "us.\n";
    std::cout << "Count: " << count << "\n";
    
    start = std::chrono::steady_clock::now();
    count = calc2(a);   
    end = std::chrono::steady_clock::now();
    std::cout << "8bit Table Execution took " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "us.\n";
    std::cout << "Count: " << count << "\n";

    start = std::chrono::steady_clock::now();
    count = calc3(a);   
    end = std::chrono::steady_clock::now();
    std::cout << "8bit Table (opt) Execution took " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "us.\n";
    std::cout << "Count: " << count << "\n";

    start = std::chrono::steady_clock::now();
    count = calc4(a);   
    end = std::chrono::steady_clock::now();
    std::cout << "8bit Table (opt2) Execution took " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "us.\n";
    std::cout << "Count: " << count << "\n";
 
    start = std::chrono::steady_clock::now();
    count = calc5(a);   
    end = std::chrono::steady_clock::now();
    std::cout << "64bit Shift Execution took " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "us.\n";
    std::cout << "Count: " << count << "\n";
}

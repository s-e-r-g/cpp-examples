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
    count = calc2(a);   
    end = std::chrono::steady_clock::now();
    std::cout << "8bit Table Execution took " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "us.\n";
    std::cout << "Count: " << count << "\n";

}

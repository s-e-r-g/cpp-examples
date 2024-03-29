#include <iostream>
#include <iomanip>
#include <ctime>
#include <chrono>
#include <vector>

// Constants and tables

constexpr std::uint8_t table8bit[256] =
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

constexpr std::uint8_t table8bitCompressed[] =
{
    0,
    1,2,
    1,2,2,
    2,3,3,4,
    1,2,2,3,2,
    2,3,3,4,3,4,
    2,3,3,4,3,4,4,
    3,4,4,5,4,5,5,6,
    1,2,2,3,2,3,3,4,2,
    2,3,3,4,3,4,4,5,3,4,
    2,3,3,4,3,4,4,5,3,4,4,
    3,4,4,5,4,5,5,6,4,5,5,6,
    2,3,3,4,3,4,4,5,3,4,4,5,4,
    3,4,4,5,4,5,5,6,4,5,5,6,5,6,
    3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,
    4,5,5,6,5,6,6,7,5,6,6,7,6,7,7,8
};

std::vector<std::uint8_t> table16bit(65536);


// Algorithms

size_t calcDirectShift(const std::vector<std::uint64_t>& array)
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

size_t calcDirectShiftOptimized(const std::vector<std::uint64_t>& array)
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

size_t calcSubtractWithMinusOne(const std::vector<std::uint64_t>& array)
{
    size_t count = 0;
    for (auto c : array)
    {
        while (c)
        {
            ++count;
            c &= (c - 1);
        }
    }

    return count;
}

size_t calc8bitTable(const std::vector<std::uint64_t>& array)
{
    size_t count = 0;
    for (auto c : array)
    {
        count += table8bit[c & 0xff];
        c >>= 8;
        count += table8bit[c & 0xff];
        c >>= 8;
        count += table8bit[c & 0xff];
        c >>= 8;
        count += table8bit[c & 0xff];
        c >>= 8;
        count += table8bit[c & 0xff];
        c >>= 8;
        count += table8bit[c & 0xff];
        c >>= 8;
        count += table8bit[c & 0xff];
        c >>= 8;
        count += table8bit[c & 0xff];
    }

    return count;
}

size_t calc8bitTableOptimized(const std::vector<std::uint64_t>& array)
{
    size_t count = 0;
    for (const auto c : array)
    {
        count += table8bit[c & 0xff];
        count += table8bit[c >> 8 & 0xff];
        count += table8bit[c >> 16 & 0xff];
        count += table8bit[c >> 24 & 0xff];
        count += table8bit[c >> 32 & 0xff];
        count += table8bit[c >> 40 & 0xff];
        count += table8bit[c >> 48 & 0xff];
        count += table8bit[c >> 56 & 0xff];
    }

    return count;
}

size_t calc8bitCompressedTable(const std::vector<std::uint64_t>& array)
{
    auto getIndex = [](std::uint8_t value)
        {
            std::uint8_t x = value & 0xf;
            std::uint8_t y = value >> 4 & 0xf;
            if (x > y)
            {
                std::swap(x, y);
            }

            return y * (y + 1) + x;
        };

    size_t count = 0;
    for (const auto c : array)
    {
        count += table8bitCompressed[getIndex(c & 0xff)];
        count += table8bitCompressed[getIndex(c >> 8 & 0xff)];
        count += table8bitCompressed[getIndex(c >> 16 & 0xff)];
        count += table8bitCompressed[getIndex(c >> 24 & 0xff)];
        count += table8bitCompressed[getIndex(c >> 32 & 0xff)];
        count += table8bitCompressed[getIndex(c >> 40 & 0xff)];
        count += table8bitCompressed[getIndex(c >> 48 & 0xff)];
        count += table8bitCompressed[getIndex(c >> 56 & 0xff)];
    }

    return count;
}

size_t calc16bitTable(const std::vector<std::uint64_t>& array)
{
    size_t count = 0;
    for (const auto c : array)
    {
        count += table16bit[c & 0xffff];
        count += table16bit[c >> 16 & 0xffff];
        count += table16bit[c >> 32 & 0xffff];
        count += table16bit[c >> 48 & 0xffff];
    }

    return count;
}

size_t calc8bitTableOptimizedV2(const std::vector<std::uint64_t>& array)
{
    size_t totalCount = 0;

    for (const auto c : array)
    {
        auto count = table8bit[c & 0xff];
        count += table8bit[c >> 8 & 0xff];
        count += table8bit[c >> 16 & 0xff];
        count += table8bit[c >> 24 & 0xff];
        count += table8bit[c >> 32 & 0xff];
        count += table8bit[c >> 40 & 0xff];
        count += table8bit[c >> 48 & 0xff];
        count += table8bit[c >> 56 & 0xff];
        totalCount += count;
    }

    return totalCount;
}

size_t calc64BitShift(const std::vector<std::uint64_t>& array)
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

constexpr std::uint64_t m1 = 0x5555555555555555;
constexpr std::uint64_t m2 = 0x3333333333333333;
constexpr std::uint64_t m3 = 0x0F0F0F0F0F0F0F0F;
constexpr std::uint64_t m4 = 0x00FF00FF00FF00FF;
constexpr std::uint64_t m5 = 0x0000FFFF0000FFFF;
constexpr std::uint64_t m6 = 0x00000000FFFFFFFF;

size_t calcTema(const std::vector<std::uint64_t>& data)
{
    std::uint64_t r32 = 0;
    for (auto value : data)
    {
        value = (value & m1) + ((value >> 1) & m1);
        value = (value & m2) + ((value >> 2) & m2);
        value = (value & m3) + ((value >> 4) & m3);
        value = (value & m4) + ((value >> 8) & m4);
        value = (value & m5) + ((value >> 16) & m5);

        r32 += value;
    }

    return (r32 & m6) + ((r32 >> 32) & m6);
}

size_t calcTema2(const std::vector<std::uint64_t>& data)
{
    std::uint64_t r32 = 0;

    const auto count = data.size();
    const auto truncatedCount = count / 30 * 30;

    size_t i = 0;
    while (i < truncatedCount)
    {
        std::uint64_t r8 = 0;
        for (std::uint8_t j = 0; j < 10; ++j)
        {
            std::uint64_t r4 = 0;
            for (std::uint8_t k = 0; k < 3; ++k)
            {
                auto value = data[i++];
                value = (value & m1) + ((value >> 1) & m1);
                value = (value & m2) + ((value >> 2) & m2);

                r4 += value;
            }

            r8 += (r4 & m3) + ((r4 >> 4) & m3);
        }

        r8 = (r8 & m4) + ((r8 >> 8) & m4);
        r8 = (r8 & m5) + ((r8 >> 16) & m5);

        r32 += r8;
    }

    for (; i < count; ++i)
    {
        auto value = data[i];
        value = (value & m1) + ((value >> 1) & m1);
        value = (value & m2) + ((value >> 2) & m2);
        value = (value & m3) + ((value >> 4) & m3);
        value = (value & m4) + ((value >> 8) & m4);
        value = (value & m5) + ((value >> 16) & m5);

        r32 += value;
    }


    return (r32 & m6) + ((r32 >> 32) & m6);
}

size_t calcTema3(const std::vector<std::uint64_t>& data)
{
    std::uint64_t r32 = 0;

    const auto count = data.size();
    const auto truncatedCount = count / 30 * 30;

    std::uint64_t i = 0;
    while (i < truncatedCount)
    {
        std::uint64_t r8 = 0;
        for (std::uint8_t j = 0; j < 10; ++j)
        {
            auto v1 = data[i++];
            auto v2 = data[i++];
            const auto v3 = data[i++];

            v1 = (v1 & m1) + ((v1 >> 1) & m1) + (v2 & m1);
            v2 = (v3 & m1) + ((v3 >> 1) & m1) + ((v2 >> 1) & m1);

            const auto r4 = (v1 & m2) + ((v1 >> 2) & m2) + (v2 & m2) + ((v2 >> 2) & m2);

            r8 += (r4 & m3) + ((r4 >> 4) & m3);
        }

        r8 = (r8 & m4) + ((r8 >> 8) & m4);
        r8 = (r8 & m5) + ((r8 >> 16) & m5);

        r32 += r8;
    }

    for (; i < count; ++i)
    {
        auto value = data[i];
        value = (value & m1) + ((value >> 1) & m1);
        value = (value & m2) + ((value >> 2) & m2);
        value = (value & m3) + ((value >> 4) & m3);
        value = (value & m4) + ((value >> 8) & m4);
        value = (value & m5) + ((value >> 16) & m5);

        r32 += value;
    }

    return (r32 & m6) + ((r32 >> 32) & m6);
}


int main()
{
    // Calculate tables
    {
        std::vector<std::uint64_t> v(1);
        for (uint64_t i = 0; i < 65536; ++i)
        {
            v[0] = i;
            table16bit[i] = calcDirectShift(v);
        }
    }


    // Fill test data
    std::vector<std::uint64_t> a(1000000);
    for (size_t i = 0; i < a.size(); ++i) a[i] = 0b1010101010101010101010101010101010101010101010101010101010101010;

    // Perform tests
    using Calculator = size_t (*)(const std::vector<std::uint64_t>&);

    struct Experiment
    {
        std::string name;
        Calculator calculator;
        std::chrono::microseconds time = {};
        size_t result = 0;
    };

    std::vector<Experiment> experiments;
    experiments.push_back({"Direct Shift", calcDirectShift});
    experiments.push_back({"Direct Shift Optimized", calcDirectShiftOptimized});
    experiments.push_back({"Subtract with minus one : n &= n - 1", calcSubtractWithMinusOne});

    experiments.push_back({"64bit Shift", calc64BitShift});

    experiments.push_back({"8bit Table", calc8bitTable});
    experiments.push_back({"8bit Table (opt)", calc8bitTableOptimized});
    experiments.push_back({"8bit Table (opt2)", calc8bitTableOptimizedV2});
    experiments.push_back({"8bit Compressed Table", calc8bitCompressedTable});

    experiments.push_back({"16bit Table", calc16bitTable});

    experiments.push_back({"Tema shift", calcTema});
    experiments.push_back({"Tema2 shift", calcTema2});
    experiments.push_back({"Tema3 shift", calcTema3});

    for (auto& experiment : experiments)
    {
        auto start = std::chrono::steady_clock::now();
        experiment.result = (experiment.calculator)(a);
        auto end = std::chrono::steady_clock::now();
        experiment.time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    }

    // Output results

    std::sort(experiments.begin(), experiments.end(), [](const auto& a, const auto& b){return a.time < b.time;});

    for (const auto& experiment : experiments)
    {
        std::cout << experiment.name << " execution time:" << experiment.time.count() << "us. (" << experiment.result << ")\n";
    }
}

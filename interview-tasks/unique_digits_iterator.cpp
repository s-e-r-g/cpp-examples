//
// Create iterator that iterates via numbers with unique digits only
// Example:
//           123, 1508 - UNIQUE
//           112, 33   - NOT UNIQUE
//
/////////////////////////////////////////////////////////////////////////


#include <iostream>
#include <iterator>
#include <bitset>

using namespace std;



class MyIterator: public std::iterator<std::input_iterator_tag, int>
{
    int cur;

public:
    MyIterator(int x)
    {
        cur = findClosestUniqueCombination(x);
    }

    MyIterator(const MyIterator& mit) :
            cur(mit.cur)
    {
    }

    MyIterator& operator++()
    {
        cur = findClosestUniqueCombination(cur + 1);
        return *this;
    }

    MyIterator operator++(int)
    {
        MyIterator tmp(*this);
        operator++();
        return tmp;
    }

    bool operator==(const MyIterator& rhs)
    {
        return cur == rhs.cur;
    }

    bool operator!=(const MyIterator& rhs)
    {
        return cur != rhs.cur;
    }

    int operator*()
    {
        return cur;
    }

private:
    static bool hasUniqueDigits(int x)
    {
        if (x == 0)
            return true;

        if (x < 0)
            x = -x;

        std::bitset<10> digitSet;
        for (; x != 0; x /= 10) {
            int digit = x % 10;

            if (digitSet[digit])
                return false;

            digitSet.set(digit);
        }

        return true;
    }

    static int findClosestUniqueCombination(int x)
    {
        for (;; ++x) {
            if (hasUniqueDigits(x))
                return x;
        }
    }
};

int main()
{
    MyIterator it(-10);

    for (int i = 0; i < 30; ++i)
    {
        cout << *(it++) << endl;
    }

    return 0;
}

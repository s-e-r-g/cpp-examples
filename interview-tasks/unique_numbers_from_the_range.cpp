// Pick random numbers from the range
// E.g. range is [1..10] and we want to pick 6 random unique numbers.


#include <iostream>
#include <vector>
#include <utility>

using namespace std;

int main()
{
    const int maxNumber = 10;
    const int getCount  = 6;

    vector<int> numbers;
    numbers.reserve(maxNumber);

    for (int i = 0; i < maxNumber; ++i)
    {
        numbers.push_back(i + 1);
    }

    for (int i = 0; i < getCount; ++i)
    {
        size_t index = rand() % (maxNumber - i) + i;
        swap(numbers[i], numbers[index]);

        cout << numbers[i] << endl;
    }
}

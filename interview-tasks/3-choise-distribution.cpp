#include <random>
#include <iostream>

bool chooseAndSwap()
{
    int prize = (std::rand() % 3000) / 1000;
    int my = (std::rand() % 3000) / 1000;

    // Exclude another empty
    int excluded = 0;
    for (; excluded < 3; ++excluded)
    {
       if (excluded != prize && excluded != my)
       {
           break;
       }
    }

    // Change my choice
    for (int i = 0; i < 3; ++i)
    {
        if (i != my && i != excluded)
        {
            my = i;
            break;
        }
    }

    return my == prize;
}


int main()
{
    const int total = 10000;
    
    int wins = 0;
    for (int i = 0; i < total; ++i)
    {
        if (chooseAndSwap()) ++wins;
    }
    
    
    std::cout << wins << " / " << total;
}

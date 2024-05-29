#include <iostream>


int main()
{
    int x = 20;
    switch (x)
    {
        case 10:
        {
            std::cout << "point 1\n";
            case 20:
            {
                std::cout << "point 2\n";
                goto label_abc;
            }
            
            std::cout << "point 3\n";
            
            label_abc:
            
                std::cout << "point 4\n";
        }
    };
}

int main()
{
    int x = 100;
    switch (x)
    {
        case 10:
        {
            std::cout << "point 1\n";
            case 20:
                {
                    std::cout << "point 2\n";
                }
        }
    };
}

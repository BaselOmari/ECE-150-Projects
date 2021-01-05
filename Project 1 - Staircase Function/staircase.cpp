#include <iostream>

int main();

int main()
{
    double x{};

    std::cout << "Enter a value of x: ";
    std::cin >> x;

    int stair{};

    int y{0};

    while (true)
    {
        if ((x>=y) && (x<y+1))
        {
            stair = y;
            break;
        }

        if ((x<(-y))&&(x>=-(y+1)))
        {
            stair = -(y+1);
            break;
        }

        ++y;
    }

    std::cout << "The value of stair(x) is: ";
    std::cout << stair;
    std::cout << std::endl;

    return 0;
}

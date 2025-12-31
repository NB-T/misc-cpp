#include <iostream>

int main()
{
    int i = 0;
    std::cout << i << std::endl;
    i++;
    std::cout << i << std::endl;
    ++i;
    std::cout << i << std::endl;

    std::cout << "++(i++): " << (++i)++ << std::endl;
    std::cout << i << std::endl;
    std::cout << ++ ++ ++i << std::endl;
    return 0;
}

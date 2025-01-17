#include <algorithm>
#include <iostream>

int main()
{
    int i = std::max({1, 2, 3});
    std::cout << i << std::endl;

    return EXIT_SUCCESS;
}

#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> v{0, 1, 3, 2, 4};
    std::sort(std::begin(v), std::end(v), std::greater<int>());
    for (auto i : v)
    {
        std::cout << i << std::endl;
    }
    std::sort(std::begin(v), std::end(v), std::less<int>());
    for (auto i : v)
    {
        std::cout << i << std::endl;
    }
}

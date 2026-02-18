#include <iostream>
#include <vector>

int* f()
{
    std::vector<int> v({1, 2, 3});
    return v.data();
}

int main()
{
    int* p = f();
    std::cout << p[1] << std::endl;
    return EXIT_SUCCESS;
}

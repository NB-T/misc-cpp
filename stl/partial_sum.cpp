#include <iostream>
#include <numeric>
#include <vector>

int main()
{
    std::vector<int> v = {1, 2, 3, 4, 5};
    int* jc = new int[v.size() + 1];
    jc[0] = 0;
    std::partial_sum(v.begin(), v.end(), jc + 1);

    for (size_t i = 0; i < v.size() + 1; ++i)
    {
        std::cout << jc[i] << ' ';
    }

    return EXIT_SUCCESS;
}
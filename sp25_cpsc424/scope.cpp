#include <omp.h>

#include <iostream>
#include <vector>

int main()
{
    const int n = 5;
    std::vector<int> data(n, 0);
    int i;
// #pragma omp parallel for shared(data) private(i)
#pragma omp parallel for shared(data)
    {
        for (int i = 0; i < n; ++i)
        {
            data[i] = i;
        }
    }
    for (auto i : data)
        std::cout << i << std::endl;

    int sum = 0;
    const int m = 10000;
#pragma omp parallel for
    for (int i = 0; i < m; ++i)
    {
        sum += 1;
    }

    std::cout << sum << std::endl;
    sum = 0;
#pragma omp parallel for reduction(+ : sum)
    for (int i = 0; i < m; ++i)
    {
        ++sum;
    }
    std::cout << sum << std::endl;
    sum = 0;
#pragma omp parallel for
    for (int i = 0; i < m; ++i)
    {
#pragma omp atomic
        ++sum;
    }
    std::cout << sum << std::endl;

    return 0;
}

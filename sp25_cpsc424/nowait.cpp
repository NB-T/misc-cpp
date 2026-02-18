#include <iostream>
#include <numeric>
#include <omp.h>
#include <vector>

int main()
{
    const int n = 10;
    const int h = 3;
    std::vector<int> a(n);
    std::iota(std::begin(a), std::end(a), 1);
    std::vector<int> b = a;
#pragma omp for nowait
    for (int i = 1; i < n - 1; ++i)
    {
        a[i] = (b[i + 1] - b[i - 1]) / (2.0 * h);
    }
#pragma omp for
    for (int i = n - 2; i > 0; --i)
    {
        b[i] = (a[i + 1] - a[i - 1]) / (2.0 * h);
    }
    return 0;
}

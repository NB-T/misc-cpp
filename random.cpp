#include <numeric>
#include <omp.h>
#include <vector>

#include <iostream>

int main()
{
    const int N = 2048;
    std::vector<int> A(N, 0);
    for (int i = 0; i < N; ++i)
    {
        A[i] = (i * 2 - 123) * (i * 2 - 123) % 4096;
    }

    /*
long long unsigned int sum = 0;
#pragma omp parallel for
for (int i = 0; i < N; ++i)
{
    sum += A[i];
}
    */

    int nt = omp_get_max_threads();
    int* partial = new int[nt]();
#pragma omp parallel
    {
        int tid = omp_get_thread_num();
#pragma omp for
        for (int i = 0; i < N; i++)
        {
            partial[tid] += A[i];
        }
    }
    int sum = 0;
    for (int t = 0; t < nt; t++)
    {
        sum += partial[t];
    }

    std::cout << sum << std::endl;

    std::cout << std::accumulate(std::begin(A), std::end(A), 0) << std::endl;
    return 0;
}

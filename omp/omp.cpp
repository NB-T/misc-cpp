#include <cmath>
#include <iostream>
#include <nbtlog/NBTlog.hpp>
#include <omp.h>
#include <random>
#include <vector>

typedef std::vector<std::vector<double>> Matrix;

double f(double x)
{
    double result = x;
    for (int i = 0; i < 5000; ++i)
    {
        result = std::sin(result) + std::cos(result) + std::sqrt(std::abs(result));
    }
    return result;
}

int main()
{
    const int N = 50000;
    std::vector<double> a(N);
    std::cout << omp_get_max_threads() << " threads" << std::endl;
    NBTlog log;
    log.start();
#pragma omp parallel for
    for (int i = 0; i < N; ++i)
    {
        a[i] = f(static_cast<double>(i));
    }
    log.log("done");

    std::cout << a[12312] << std::endl;

#if defined(_OPENMP)
    std::cout << "good" << std::endl;
#else
    std::cout << "bad" << std::endl;
#endif

    return 0;
}

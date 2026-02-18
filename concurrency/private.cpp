#include <iostream>
#include <omp.h>

int main()
{
    int c = 0;
#pragma omp parallel for reduction(+ : c)
    for (int i = 0; i < 100; ++i)
    {
        ++c;
    }

    std::cout << c << std::endl;
}

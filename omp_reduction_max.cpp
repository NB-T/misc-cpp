#include <omp.h>

#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    int nrows = 0;
#pragma omp parallel for schedule(static) reduction(max \
                                                    : nrows)
    for (int i = 0; i < 25; ++i)
    {
        // std::cout << (i + 10) % 20 << '\n';
        nrows = (i + 10) % 20;
    }

    std::cout << "THINGY " << nrows << '\n';

    return EXIT_SUCCESS;
}
